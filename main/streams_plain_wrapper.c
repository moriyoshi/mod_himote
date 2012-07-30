/*
   +----------------------------------------------------------------------+
   | HIMOTE Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2012 The HIMOTE Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the HIMOTE license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.himote.net/license/3_01.txt                                  |
   | If you did not receive a copy of the HIMOTE license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Wez Furlong <wez@thebrainroom.com>                          |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#include "himote.h"
#include "himote_globals.h"
#include "himote_network.h"
#include "himote_open_temporary_file.h"
#include "himote_file.h"
#include "himote_flock_compat.h"
#include "himote_filestat.h"
#include <stddef.h>
#include <fcntl.h>
#if HAVE_SYS_WAIT_H
#include <sys/wait.h>
#endif
#if HAVE_SYS_FILE_H
#include <sys/file.h>
#endif
#ifdef HAVE_SYS_MMAN_H
#include <sys/mman.h>
#endif
#include "SAPI.h"

#include "himote_streams_int.h"
#ifdef HIMOTE_WIN32
# include "win32/winutil.h"
#endif

#define himote_stream_fopen_from_fd_int(fd, mode, persistent_id)	_himote_stream_fopen_from_fd_int((fd), (mode), (persistent_id) STREAMS_CC TSRMLS_CC)
#define himote_stream_fopen_from_fd_int_rel(fd, mode, persistent_id)	 _himote_stream_fopen_from_fd_int((fd), (mode), (persistent_id) STREAMS_REL_CC TSRMLS_CC)
#define himote_stream_fopen_from_file_int(file, mode)	_himote_stream_fopen_from_file_int((file), (mode) STREAMS_CC TSRMLS_CC)
#define himote_stream_fopen_from_file_int_rel(file, mode)	 _himote_stream_fopen_from_file_int((file), (mode) STREAMS_REL_CC TSRMLS_CC)

/* parse standard "fopen" modes into open() flags */
HIMOTEAPI int himote_stream_parse_fopen_modes(const char *mode, int *open_flags)
{
	int flags;

	switch (mode[0]) {
		case 'r':
			flags = 0;
			break;
		case 'w':
			flags = O_TRUNC|O_CREAT;
			break;
		case 'a':
			flags = O_CREAT|O_APPEND;
			break;
		case 'x':
			flags = O_CREAT|O_EXCL;
			break;
		case 'c':
			flags = O_CREAT;
			break;
		default:
			/* unknown mode */
			return FAILURE;
	}
#if defined(O_NONBLOCK)
	if (strchr(mode, 'n')) {
		flags |= O_NONBLOCK;
	}
#endif
	if (strchr(mode, '+')) {
		flags |= O_RDWR;
	} else if (flags) {
		flags |= O_WRONLY;
	} else {
		flags |= O_RDONLY;
	}

#if defined(_O_TEXT) && defined(O_BINARY)
	if (strchr(mode, 't')) {
		flags |= _O_TEXT;
	} else {
		flags |= O_BINARY;
	}
#endif

	*open_flags = flags;
	return SUCCESS;
}


/* {{{ ------- STDIO stream implementation -------*/

typedef struct {
	FILE *file;
	int fd;					/* underlying file descriptor */
	unsigned is_process_pipe:1;	/* use pclose instead of fclose */
	unsigned is_pipe:1;			/* don't try and seek */
	unsigned cached_fstat:1;	/* sb is valid */
	unsigned _reserved:29;
	
	int lock_flag;			/* stores the lock state */
	char *temp_file_name;	/* if non-null, this is the path to a temporary file that
							 * is to be deleted when the stream is closed */
#if HAVE_FLUSHIO
	char last_op;
#endif

#if HAVE_MMAP
	char *last_mapped_addr;
	size_t last_mapped_len;
#endif
#ifdef HIMOTE_WIN32
	char *last_mapped_addr;
	HANDLE file_mapping;
#endif

	struct stat sb;
} himote_stdio_stream_data;
#define HIMOTE_STDIOP_GET_FD(anfd, data)	anfd = (data)->file ? fileno((data)->file) : (data)->fd

static int do_fstat(himote_stdio_stream_data *d, int force)
{
	if (!d->cached_fstat || force) {
		int fd;
		int r;
	   
		HIMOTE_STDIOP_GET_FD(fd, d);
		r = fstat(fd, &d->sb);
		d->cached_fstat = r == 0;

		return r;
	}
	return 0;
}

static himote_stream *_himote_stream_fopen_from_fd_int(int fd, const char *mode, const char *persistent_id STREAMS_DC TSRMLS_DC)
{
	himote_stdio_stream_data *self;
	
	self = pemalloc_rel_orig(sizeof(*self), persistent_id);
	memset(self, 0, sizeof(*self));
	self->file = NULL;
	self->is_pipe = 0;
	self->lock_flag = LOCK_UN;
	self->is_process_pipe = 0;
	self->temp_file_name = NULL;
	self->fd = fd;
	
	return himote_stream_alloc_rel(&himote_stream_stdio_ops, self, persistent_id, mode);
}

static himote_stream *_himote_stream_fopen_from_file_int(FILE *file, const char *mode STREAMS_DC TSRMLS_DC)
{
	himote_stdio_stream_data *self;
	
	self = emalloc_rel_orig(sizeof(*self));
	memset(self, 0, sizeof(*self));
	self->file = file;
	self->is_pipe = 0;
	self->lock_flag = LOCK_UN;
	self->is_process_pipe = 0;
	self->temp_file_name = NULL;
	self->fd = fileno(file);

	return himote_stream_alloc_rel(&himote_stream_stdio_ops, self, 0, mode);
}

HIMOTEAPI himote_stream *_himote_stream_fopen_temporary_file(const char *dir, const char *pfx, char **opened_path STREAMS_DC TSRMLS_DC)
{
	int fd = himote_open_temporary_fd(dir, pfx, opened_path TSRMLS_CC);

	if (fd != -1)	{
		himote_stream *stream = himote_stream_fopen_from_fd_int_rel(fd, "r+b", NULL);
		if (stream) {
			return stream;
		}
		close(fd);

		himote_error_docref(NULL TSRMLS_CC, E_WARNING, "unable to allocate stream");

		return NULL;
	}
	return NULL;
}

HIMOTEAPI himote_stream *_himote_stream_fopen_tmpfile(int dummy STREAMS_DC TSRMLS_DC)
{
	char *opened_path = NULL;
	int fd = himote_open_temporary_fd(NULL, "himote", &opened_path TSRMLS_CC);

	if (fd != -1)	{
		himote_stream *stream = himote_stream_fopen_from_fd_int_rel(fd, "r+b", NULL);
		if (stream) {
			himote_stdio_stream_data *self = (himote_stdio_stream_data*)stream->abstract;
			stream->wrapper = &himote_plain_files_wrapper;
			stream->orig_path = estrdup(opened_path);

			self->temp_file_name = opened_path;
			self->lock_flag = LOCK_UN;
			
			return stream;
		}
		close(fd);

		himote_error_docref(NULL TSRMLS_CC, E_WARNING, "unable to allocate stream");

		return NULL;
	}
	return NULL;
}

HIMOTEAPI himote_stream *_himote_stream_fopen_from_fd(int fd, const char *mode, const char *persistent_id STREAMS_DC TSRMLS_DC)
{
	himote_stream *stream = himote_stream_fopen_from_fd_int_rel(fd, mode, persistent_id);

	if (stream) {
		himote_stdio_stream_data *self = (himote_stdio_stream_data*)stream->abstract;

#ifdef S_ISFIFO
		/* detect if this is a pipe */
		if (self->fd >= 0) {
			self->is_pipe = (do_fstat(self, 0) == 0 && S_ISFIFO(self->sb.st_mode)) ? 1 : 0;
		}
#elif defined(HIMOTE_WIN32)
		{
			zend_uintptr_t handle = _get_osfhandle(self->fd);

			if (handle != (zend_uintptr_t)INVALID_HANDLE_VALUE) {
				self->is_pipe = GetFileType((HANDLE)handle) == FILE_TYPE_PIPE;
			}
		}
#endif
	
		if (self->is_pipe) {
			stream->flags |= HIMOTE_STREAM_FLAG_NO_SEEK;
		} else {
			stream->position = lseek(self->fd, 0, SEEK_CUR);
#ifdef ESPIPE
			if (stream->position == (off_t)-1 && errno == ESPIPE) {
				stream->position = 0;
				stream->flags |= HIMOTE_STREAM_FLAG_NO_SEEK;
				self->is_pipe = 1;
			}
#endif
		}
	}

	return stream;
}

HIMOTEAPI himote_stream *_himote_stream_fopen_from_file(FILE *file, const char *mode STREAMS_DC TSRMLS_DC)
{
	himote_stream *stream = himote_stream_fopen_from_file_int_rel(file, mode);

	if (stream) {
		himote_stdio_stream_data *self = (himote_stdio_stream_data*)stream->abstract;

#ifdef S_ISFIFO
		/* detect if this is a pipe */
		if (self->fd >= 0) {
			self->is_pipe = (do_fstat(self, 0) == 0 && S_ISFIFO(self->sb.st_mode)) ? 1 : 0;
		}
#elif defined(HIMOTE_WIN32)
		{
			zend_uintptr_t handle = _get_osfhandle(self->fd);

			if (handle != (zend_uintptr_t)INVALID_HANDLE_VALUE) {
				self->is_pipe = GetFileType((HANDLE)handle) == FILE_TYPE_PIPE;
			}
		}
#endif
	
		if (self->is_pipe) {
			stream->flags |= HIMOTE_STREAM_FLAG_NO_SEEK;
		} else {
			stream->position = ftell(file);
		}
	}

	return stream;
}

HIMOTEAPI himote_stream *_himote_stream_fopen_from_pipe(FILE *file, const char *mode STREAMS_DC TSRMLS_DC)
{
	himote_stdio_stream_data *self;
	himote_stream *stream;

	self = emalloc_rel_orig(sizeof(*self));
	memset(self, 0, sizeof(*self));
	self->file = file;
	self->is_pipe = 1;
	self->lock_flag = LOCK_UN;
	self->is_process_pipe = 1;
	self->fd = fileno(file);
	self->temp_file_name = NULL;

	stream = himote_stream_alloc_rel(&himote_stream_stdio_ops, self, 0, mode);
	stream->flags |= HIMOTE_STREAM_FLAG_NO_SEEK;
	return stream;
}

static size_t himote_stdiop_write(himote_stream *stream, const char *buf, size_t count TSRMLS_DC)
{
	himote_stdio_stream_data *data = (himote_stdio_stream_data*)stream->abstract;

	assert(data != NULL);

	if (data->fd >= 0) {
		int bytes_written = write(data->fd, buf, count);
		if (bytes_written < 0) return 0;
		return (size_t) bytes_written;
	} else {

#if HAVE_FLUSHIO
		if (!data->is_pipe && data->last_op == 'r') {
			fseek(data->file, 0, SEEK_CUR);
		}
		data->last_op = 'w';
#endif

		return fwrite(buf, 1, count, data->file);
	}
}

static size_t himote_stdiop_read(himote_stream *stream, char *buf, size_t count TSRMLS_DC)
{
	himote_stdio_stream_data *data = (himote_stdio_stream_data*)stream->abstract;
	size_t ret;

	assert(data != NULL);

	if (data->fd >= 0) {
		ret = read(data->fd, buf, count);

		if (ret == (size_t)-1 && errno == EINTR) {
			/* Read was interrupted, retry once,
			   If read still fails, giveup with feof==0
			   so script can retry if desired */
			ret = read(data->fd, buf, count);
		}
		
		stream->eof = (ret == 0 || (ret == (size_t)-1 && errno != EWOULDBLOCK && errno != EINTR && errno != EBADF));
				
	} else {
#if HAVE_FLUSHIO
		if (!data->is_pipe && data->last_op == 'w')
			fseek(data->file, 0, SEEK_CUR);
		data->last_op = 'r';
#endif

		ret = fread(buf, 1, count, data->file);

		stream->eof = feof(data->file);
	}
	return ret;
}

static int himote_stdiop_close(himote_stream *stream, int close_handle TSRMLS_DC)
{
	int ret;
	himote_stdio_stream_data *data = (himote_stdio_stream_data*)stream->abstract;

	assert(data != NULL);

#if HAVE_MMAP
	if (data->last_mapped_addr) {
		munmap(data->last_mapped_addr, data->last_mapped_len);
		data->last_mapped_addr = NULL;
	}
#elif defined(HIMOTE_WIN32)
	if (data->last_mapped_addr) {
		UnmapViewOfFile(data->last_mapped_addr);
		data->last_mapped_addr = NULL;
	}
	if (data->file_mapping) {
		CloseHandle(data->file_mapping);
		data->file_mapping = NULL;
	}
#endif
	
	if (close_handle) {
		if (data->file) {
			if (data->is_process_pipe) {
				errno = 0;
				ret = pclose(data->file);

#if HAVE_SYS_WAIT_H
				if (WIFEXITED(ret)) {
					ret = WEXITSTATUS(ret);
				}
#endif
			} else {
				ret = fclose(data->file);
				data->file = NULL;
			}
		} else if (data->fd != -1) {
			ret = close(data->fd);
			data->fd = -1;
		} else {
			return 0; /* everything should be closed already -> success */
		}
		if (data->temp_file_name) {
			unlink(data->temp_file_name);
			/* temporary streams are never persistent */
			efree(data->temp_file_name);
			data->temp_file_name = NULL;
		}
	} else {
		ret = 0;
		data->file = NULL;
		data->fd = -1;
	}

	pefree(data, stream->is_persistent);

	return ret;
}

static int himote_stdiop_flush(himote_stream *stream TSRMLS_DC)
{
	himote_stdio_stream_data *data = (himote_stdio_stream_data*)stream->abstract;

	assert(data != NULL);

	/*
	 * stdio buffers data in user land. By calling fflush(3), this
	 * data is send to the kernel using write(2). fsync'ing is
	 * something completely different.
	 */
	if (data->file) {
		return fflush(data->file);
	}
	return 0;
}

static int himote_stdiop_seek(himote_stream *stream, off_t offset, int whence, off_t *newoffset TSRMLS_DC)
{
	himote_stdio_stream_data *data = (himote_stdio_stream_data*)stream->abstract;
	int ret;

	assert(data != NULL);

	if (data->is_pipe) {
		himote_error_docref(NULL TSRMLS_CC, E_WARNING, "cannot seek on a pipe");
		return -1;
	}

	if (data->fd >= 0) {
		off_t result;
		
		result = lseek(data->fd, offset, whence);
		if (result == (off_t)-1)
			return -1;

		*newoffset = result;
		return 0;
		
	} else {
		ret = fseek(data->file, offset, whence);
		*newoffset = ftell(data->file);
		return ret;
	}
}

static int himote_stdiop_cast(himote_stream *stream, int castas, void **ret TSRMLS_DC)
{
	int fd;
	himote_stdio_stream_data *data = (himote_stdio_stream_data*) stream->abstract;

	assert(data != NULL);
	
	/* as soon as someone touches the stdio layer, buffering may ensue,
	 * so we need to stop using the fd directly in that case */

	switch (castas)	{
		case HIMOTE_STREAM_AS_STDIO:
			if (ret) {

				if (data->file == NULL) {
					/* we were opened as a plain file descriptor, so we
					 * need fdopen now */
					char fixed_mode[5];
					himote_stream_mode_sanitize_fdopen_fopencookie(stream, fixed_mode);
					data->file = fdopen(data->fd, fixed_mode);
					if (data->file == NULL) {
						return FAILURE;
					}
				}
				
				*(FILE**)ret = data->file;
				data->fd = -1;
			}
			return SUCCESS;

		case HIMOTE_STREAM_AS_FD_FOR_SELECT:
			HIMOTE_STDIOP_GET_FD(fd, data);
			if (fd < 0) {
				return FAILURE;
			}
			if (ret) {
				*(int*)ret = fd;
			}
			return SUCCESS;

		case HIMOTE_STREAM_AS_FD:
			HIMOTE_STDIOP_GET_FD(fd, data);

			if (fd < 0) {
				return FAILURE;
			}
			if (data->file) {
				fflush(data->file);
			}
			if (ret) {
				*(int*)ret = fd;
			}
			return SUCCESS;
		default:
			return FAILURE;
	}
}

static int himote_stdiop_stat(himote_stream *stream, himote_stream_statbuf *ssb TSRMLS_DC)
{
	int ret;
	himote_stdio_stream_data *data = (himote_stdio_stream_data*) stream->abstract;

	assert(data != NULL);

	ret = do_fstat(data, 1);
	memcpy(&ssb->sb, &data->sb, sizeof(ssb->sb));
	return ret;
}

static int himote_stdiop_set_option(himote_stream *stream, int option, int value, void *ptrparam TSRMLS_DC)
{
	himote_stdio_stream_data *data = (himote_stdio_stream_data*) stream->abstract;
	size_t size;
	int fd;
#ifdef O_NONBLOCK
	/* FIXME: make this work for win32 */
	int flags;
	int oldval;
#endif
	
	HIMOTE_STDIOP_GET_FD(fd, data);
	
	switch(option) {
		case HIMOTE_STREAM_OPTION_BLOCKING:
			if (fd == -1)
				return -1;
#ifdef O_NONBLOCK
			flags = fcntl(fd, F_GETFL, 0);
			oldval = (flags & O_NONBLOCK) ? 0 : 1;
			if (value)
				flags &= ~O_NONBLOCK;
			else
				flags |= O_NONBLOCK;
			
			if (-1 == fcntl(fd, F_SETFL, flags))
				return -1;
			return oldval;
#else
			return -1; /* not yet implemented */
#endif
			
		case HIMOTE_STREAM_OPTION_WRITE_BUFFER:

			if (data->file == NULL) {
				return -1;
			}
			
			if (ptrparam)
				size = *(size_t *)ptrparam;
			else
				size = BUFSIZ;

			switch(value) {
				case HIMOTE_STREAM_BUFFER_NONE:
					stream->flags |= HIMOTE_STREAM_FLAG_NO_BUFFER;
					return setvbuf(data->file, NULL, _IONBF, 0);
					
				case HIMOTE_STREAM_BUFFER_LINE:
					stream->flags ^= HIMOTE_STREAM_FLAG_NO_BUFFER;
					return setvbuf(data->file, NULL, _IOLBF, size);
					
				case HIMOTE_STREAM_BUFFER_FULL:
					stream->flags ^= HIMOTE_STREAM_FLAG_NO_BUFFER;
					return setvbuf(data->file, NULL, _IOFBF, size);

				default:
					return -1;
			}
			break;
		
		case HIMOTE_STREAM_OPTION_LOCKING:
			if (fd == -1) {
				return -1;
			}

			if ((zend_uintptr_t) ptrparam == HIMOTE_STREAM_LOCK_SUPPORTED) {
				return 0;
			}

			if (!flock(fd, value)) {
				data->lock_flag = value;
				return 0;
			} else {
				return -1;
			}
			break;

		case HIMOTE_STREAM_OPTION_MMAP_API:
#if HAVE_MMAP
			{
				himote_stream_mmap_range *range = (himote_stream_mmap_range*)ptrparam;
				int prot, flags;
				
				switch (value) {
					case HIMOTE_STREAM_MMAP_SUPPORTED:
						return fd == -1 ? HIMOTE_STREAM_OPTION_RETURN_ERR : HIMOTE_STREAM_OPTION_RETURN_OK;

					case HIMOTE_STREAM_MMAP_MAP_RANGE:
						do_fstat(data, 1);
						if (range->length == 0 && range->offset > 0 && range->offset < data->sb.st_size) {
							range->length = data->sb.st_size - range->offset;
						}
						if (range->length == 0 || range->length > data->sb.st_size) {
							range->length = data->sb.st_size;
						}
						if (range->offset >= data->sb.st_size) {
							range->offset = data->sb.st_size;
							range->length = 0;
						}
						switch (range->mode) {
							case HIMOTE_STREAM_MAP_MODE_READONLY:
								prot = PROT_READ;
								flags = MAP_PRIVATE;
								break;
							case HIMOTE_STREAM_MAP_MODE_READWRITE:
								prot = PROT_READ | PROT_WRITE;
								flags = MAP_PRIVATE;
								break;
							case HIMOTE_STREAM_MAP_MODE_SHARED_READONLY:
								prot = PROT_READ;
								flags = MAP_SHARED;
								break;
							case HIMOTE_STREAM_MAP_MODE_SHARED_READWRITE:
								prot = PROT_READ | PROT_WRITE;
								flags = MAP_SHARED;
								break;
							default:
								return HIMOTE_STREAM_OPTION_RETURN_ERR;
						}
						range->mapped = (char*)mmap(NULL, range->length, prot, flags, fd, range->offset);
						if (range->mapped == (char*)MAP_FAILED) {
							range->mapped = NULL;
							return HIMOTE_STREAM_OPTION_RETURN_ERR;
						}
						/* remember the mapping */
						data->last_mapped_addr = range->mapped;
						data->last_mapped_len = range->length;
						return HIMOTE_STREAM_OPTION_RETURN_OK;

					case HIMOTE_STREAM_MMAP_UNMAP:
						if (data->last_mapped_addr) {
							munmap(data->last_mapped_addr, data->last_mapped_len);
							data->last_mapped_addr = NULL;

							return HIMOTE_STREAM_OPTION_RETURN_OK;
						}
						return HIMOTE_STREAM_OPTION_RETURN_ERR;
				}
			}
#elif defined(HIMOTE_WIN32)
			{
				himote_stream_mmap_range *range = (himote_stream_mmap_range*)ptrparam;
				HANDLE hfile = (HANDLE)_get_osfhandle(fd);
				DWORD prot, acc, loffs = 0, delta = 0;

				switch (value) {
					case HIMOTE_STREAM_MMAP_SUPPORTED:
						return hfile == INVALID_HANDLE_VALUE ? HIMOTE_STREAM_OPTION_RETURN_ERR : HIMOTE_STREAM_OPTION_RETURN_OK;

					case HIMOTE_STREAM_MMAP_MAP_RANGE:
						switch (range->mode) {
							case HIMOTE_STREAM_MAP_MODE_READONLY:
								prot = PAGE_READONLY;
								acc = FILE_MAP_READ;
								break;
							case HIMOTE_STREAM_MAP_MODE_READWRITE:
								prot = PAGE_READWRITE;
								acc = FILE_MAP_READ | FILE_MAP_WRITE;
								break;
							case HIMOTE_STREAM_MAP_MODE_SHARED_READONLY:
								prot = PAGE_READONLY;
								acc = FILE_MAP_READ;
								/* TODO: we should assign a name for the mapping */
								break;
							case HIMOTE_STREAM_MAP_MODE_SHARED_READWRITE:
								prot = PAGE_READWRITE;
								acc = FILE_MAP_READ | FILE_MAP_WRITE;
								/* TODO: we should assign a name for the mapping */
								break;
							default:
								return HIMOTE_STREAM_OPTION_RETURN_ERR;
						}

						/* create a mapping capable of viewing the whole file (this costs no real resources) */
						data->file_mapping = CreateFileMapping(hfile, NULL, prot, 0, 0, NULL);

						if (data->file_mapping == NULL) {
							return HIMOTE_STREAM_OPTION_RETURN_ERR;
						}

						size = GetFileSize(hfile, NULL);
						if (range->length == 0 && range->offset > 0 && range->offset < size) {
							range->length = size - range->offset;
						}
						if (range->length == 0 || range->length > size) {
							range->length = size;
						}
						if (range->offset >= size) {
							range->offset = size;
							range->length = 0;
						}

						/* figure out how big a chunk to map to be able to view the part that we need */
						if (range->offset != 0) {
							SYSTEM_INFO info;
							DWORD gran;

							GetSystemInfo(&info);
							gran = info.dwAllocationGranularity;
							loffs = (range->offset / gran) * gran;
							delta = range->offset - loffs;
						}

						data->last_mapped_addr = MapViewOfFile(data->file_mapping, acc, 0, loffs, range->length + delta);

						if (data->last_mapped_addr) {
							/* give them back the address of the start offset they requested */
							range->mapped = data->last_mapped_addr + delta;
							return HIMOTE_STREAM_OPTION_RETURN_OK;
						}

						CloseHandle(data->file_mapping);
						data->file_mapping = NULL;

						return HIMOTE_STREAM_OPTION_RETURN_ERR;

					case HIMOTE_STREAM_MMAP_UNMAP:
						if (data->last_mapped_addr) {
							UnmapViewOfFile(data->last_mapped_addr);
							data->last_mapped_addr = NULL;
							CloseHandle(data->file_mapping);
							data->file_mapping = NULL;
							return HIMOTE_STREAM_OPTION_RETURN_OK;
						}
						return HIMOTE_STREAM_OPTION_RETURN_ERR;

					default:
						return HIMOTE_STREAM_OPTION_RETURN_ERR;
				}
			}

#endif
			return HIMOTE_STREAM_OPTION_RETURN_NOTIMPL;

		case HIMOTE_STREAM_OPTION_TRUNCATE_API:
			switch (value) {
				case HIMOTE_STREAM_TRUNCATE_SUPPORTED:
					return fd == -1 ? HIMOTE_STREAM_OPTION_RETURN_ERR : HIMOTE_STREAM_OPTION_RETURN_OK;

				case HIMOTE_STREAM_TRUNCATE_SET_SIZE: {
					ptrdiff_t new_size = *(ptrdiff_t*)ptrparam;
					if (new_size < 0) {
						return HIMOTE_STREAM_OPTION_RETURN_ERR;
					}
					return ftruncate(fd, new_size) == 0 ? HIMOTE_STREAM_OPTION_RETURN_OK : HIMOTE_STREAM_OPTION_RETURN_ERR;
				}
			}
			
		default:
			return HIMOTE_STREAM_OPTION_RETURN_NOTIMPL;
	}
}

HIMOTEAPI himote_stream_ops	himote_stream_stdio_ops = {
	himote_stdiop_write, himote_stdiop_read,
	himote_stdiop_close, himote_stdiop_flush,
	"STDIO",
	himote_stdiop_seek,
	himote_stdiop_cast,
	himote_stdiop_stat,
	himote_stdiop_set_option
};
/* }}} */

/* {{{ plain files opendir/readdir implementation */
static size_t himote_plain_files_dirstream_read(himote_stream *stream, char *buf, size_t count TSRMLS_DC)
{
	DIR *dir = (DIR*)stream->abstract;
	/* avoid libc5 readdir problems */
	char entry[sizeof(struct dirent)+MAXPATHLEN];
	struct dirent *result = (struct dirent *)&entry;
	himote_stream_dirent *ent = (himote_stream_dirent*)buf;

	/* avoid problems if someone mis-uses the stream */
	if (count != sizeof(himote_stream_dirent))
		return 0;

	if (himote_readdir_r(dir, (struct dirent *)entry, &result) == 0 && result) {
		HIMOTE_STRLCPY(ent->d_name, result->d_name, sizeof(ent->d_name), strlen(result->d_name));
		return sizeof(himote_stream_dirent);
	}
	return 0;
}

static int himote_plain_files_dirstream_close(himote_stream *stream, int close_handle TSRMLS_DC)
{
	return closedir((DIR *)stream->abstract);
}

static int himote_plain_files_dirstream_rewind(himote_stream *stream, off_t offset, int whence, off_t *newoffs TSRMLS_DC)
{
	rewinddir((DIR *)stream->abstract);
	return 0;
}

static himote_stream_ops	himote_plain_files_dirstream_ops = {
	NULL, himote_plain_files_dirstream_read,
	himote_plain_files_dirstream_close, NULL,
	"dir",
	himote_plain_files_dirstream_rewind,
	NULL, /* cast */
	NULL, /* stat */
	NULL  /* set_option */
};

static himote_stream *himote_plain_files_dir_opener(himote_stream_wrapper *wrapper, char *path, char *mode,
		int options, char **opened_path, himote_stream_context *context STREAMS_DC TSRMLS_DC)
{
	DIR *dir = NULL;
	himote_stream *stream = NULL;

#ifdef HAVE_GLOB
	if (options & STREAM_USE_GLOB_DIR_OPEN) {
		return himote_glob_stream_wrapper.wops->dir_opener(&himote_glob_stream_wrapper, path, mode, options, opened_path, context STREAMS_REL_CC TSRMLS_CC);
	}
#endif

	if (((options & STREAM_DISABLE_OPEN_BASEDIR) == 0) && himote_check_open_basedir(path TSRMLS_CC)) {
		return NULL;
	}
	
	dir = VCWD_OPENDIR(path);

#ifdef HIMOTE_WIN32
	if (!dir) {
		himote_win32_docref2_from_error(GetLastError(), path, path TSRMLS_CC);
	}

	if (dir && dir->finished) {
		closedir(dir);
		dir = NULL;
	}
#endif
	if (dir) {
		stream = himote_stream_alloc(&himote_plain_files_dirstream_ops, dir, 0, mode);
		if (stream == NULL)
			closedir(dir);
	}
		
	return stream;
}
/* }}} */

/* {{{ himote_stream_fopen */
HIMOTEAPI himote_stream *_himote_stream_fopen(const char *filename, const char *mode, char **opened_path, int options STREAMS_DC TSRMLS_DC)
{
	char *realpath = NULL;
	int open_flags;
	int fd;
	himote_stream *ret;
	int persistent = options & STREAM_OPEN_PERSISTENT;
	char *persistent_id = NULL;

	if (FAILURE == himote_stream_parse_fopen_modes(mode, &open_flags)) {
		if (options & REPORT_ERRORS) {
			himote_error_docref(NULL TSRMLS_CC, E_WARNING, "`%s' is not a valid mode for fopen", mode);
		}
		return NULL;
	}

	if (options & STREAM_ASSUME_REALPATH) {
		realpath = estrdup(filename);
	} else {
		if ((realpath = expand_filepath(filename, NULL TSRMLS_CC)) == NULL) {
			return NULL;
		}
	}

	if (persistent) {
		spprintf(&persistent_id, 0, "streams_stdio_%d_%s", open_flags, realpath);
		switch (himote_stream_from_persistent_id(persistent_id, &ret TSRMLS_CC)) {
			case HIMOTE_STREAM_PERSISTENT_SUCCESS:
				if (opened_path) {
					*opened_path = realpath;
					realpath = NULL;
				}
				/* fall through */

			case HIMOTE_STREAM_PERSISTENT_FAILURE:
				if (realpath) {
					efree(realpath);
				}
				efree(persistent_id);;
				return ret;
		}
	}
	
	fd = open(realpath, open_flags, 0666);

	if (fd != -1)	{

		if (options & STREAM_OPEN_FOR_INCLUDE) {
			ret = himote_stream_fopen_from_fd_int_rel(fd, mode, persistent_id);
		} else {
			ret = himote_stream_fopen_from_fd_rel(fd, mode, persistent_id);
		}

		if (ret)	{
			if (opened_path) {
				*opened_path = realpath;
				realpath = NULL;
			}
			if (realpath) {
				efree(realpath);
			}
			if (persistent_id) {
				efree(persistent_id);
			}

			/* WIN32 always set ISREG flag */
#ifndef HIMOTE_WIN32
			/* sanity checks for include/require.
			 * We check these after opening the stream, so that we save
			 * on fstat() syscalls */
			if (options & STREAM_OPEN_FOR_INCLUDE) {
				himote_stdio_stream_data *self = (himote_stdio_stream_data*)ret->abstract;
				int r;

				r = do_fstat(self, 0);
				if ((r == 0 && !S_ISREG(self->sb.st_mode))) {
					if (opened_path) {
						efree(*opened_path);
						*opened_path = NULL;
					}
					himote_stream_close(ret);
					return NULL;
				}
			}
#endif

			return ret;
		}
		close(fd);
	}
	efree(realpath);
	if (persistent_id) {
		efree(persistent_id);
	}
	return NULL;
}
/* }}} */


static himote_stream *himote_plain_files_stream_opener(himote_stream_wrapper *wrapper, char *path, char *mode,
		int options, char **opened_path, himote_stream_context *context STREAMS_DC TSRMLS_DC)
{
	if (((options & STREAM_DISABLE_OPEN_BASEDIR) == 0) && himote_check_open_basedir(path TSRMLS_CC)) {
		return NULL;
	}

	if ((himote_check_safe_mode_include_dir(path TSRMLS_CC)) == 0) {
		return himote_stream_fopen_rel(path, mode, opened_path, options);
	}

	return himote_stream_fopen_rel(path, mode, opened_path, options);
}

static int himote_plain_files_url_stater(himote_stream_wrapper *wrapper, char *url, int flags, himote_stream_statbuf *ssb, himote_stream_context *context TSRMLS_DC)
{
	char *p;

	if ((p = strstr(url, "://")) != NULL) {
		if (p < strchr(url, '/')) {
			url = p + 3;
		}
	}

	if (himote_check_open_basedir_ex(url, (flags & HIMOTE_STREAM_URL_STAT_QUIET) ? 0 : 1 TSRMLS_CC)) {
		return -1;
	}

#ifdef HIMOTE_WIN32
	if (EG(windows_version_info).dwMajorVersion >= 5) {
		if (flags & HIMOTE_STREAM_URL_STAT_LINK) {
			return VCWD_LSTAT(url, &ssb->sb);
		}
	}
#else
# ifdef HAVE_SYMLINK
	if (flags & HIMOTE_STREAM_URL_STAT_LINK) {
		return VCWD_LSTAT(url, &ssb->sb);
	} else
# endif
#endif
		return VCWD_STAT(url, &ssb->sb);
}

static int himote_plain_files_unlink(himote_stream_wrapper *wrapper, char *url, int options, himote_stream_context *context TSRMLS_DC)
{
	char *p;
	int ret;

	if ((p = strstr(url, "://")) != NULL) {
		if (p < strchr(url, '/')) {
			url = p + 3;
		}
	}

	ret = VCWD_UNLINK(url);
	if (ret == -1) {
		if (options & REPORT_ERRORS) {
			himote_error_docref1(NULL TSRMLS_CC, url, E_WARNING, "%s", strerror(errno));
		}
		return 0;
	}

	/* Clear stat cache (and realpath cache) */
	himote_clear_stat_cache(1, NULL, 0 TSRMLS_CC);

	return 1;
}

static int himote_plain_files_rename(himote_stream_wrapper *wrapper, char *url_from, char *url_to, int options, himote_stream_context *context TSRMLS_DC)
{
	char *p;
	int ret;

	if (!url_from || !url_to) {
		return 0;
	}

#ifdef HIMOTE_WIN32
	if (!himote_win32_check_trailing_space(url_from, strlen(url_from))) {
		himote_win32_docref2_from_error(ERROR_INVALID_NAME, url_from, url_to TSRMLS_CC);
		return 0;
	}
	if (!himote_win32_check_trailing_space(url_to, strlen(url_to))) {
		himote_win32_docref2_from_error(ERROR_INVALID_NAME, url_from, url_to TSRMLS_CC);
		return 0;
	}
#endif

	if ((p = strstr(url_from, "://")) != NULL) {
		if (p < strchr(url_from, '/')) {
			url_from = p + 3;
		}
	}

	if ((p = strstr(url_to, "://")) != NULL) {
		if (p < strchr(url_to, '/')) {
			url_to = p + 3;
		}
	}

	if (himote_check_open_basedir(url_from TSRMLS_CC) || himote_check_open_basedir(url_to TSRMLS_CC)) {
		return 0;
	}

	ret = VCWD_RENAME(url_from, url_to);

	if (ret == -1) {
#ifndef HIMOTE_WIN32
# ifdef EXDEV
		if (errno == EXDEV) {
			struct stat sb;
			if (himote_copy_file(url_from, url_to TSRMLS_CC) == SUCCESS) {
				if (VCWD_STAT(url_from, &sb) == 0) {
#  if !defined(TSRM_WIN32) && !defined(NETWARE)
					if (VCWD_CHMOD(url_to, sb.st_mode)) {
						if (errno == EPERM) {
							himote_error_docref2(NULL TSRMLS_CC, url_from, url_to, E_WARNING, "%s", strerror(errno));
							VCWD_UNLINK(url_from);
							return 1;
						}
						himote_error_docref2(NULL TSRMLS_CC, url_from, url_to, E_WARNING, "%s", strerror(errno));
						return 0;
					}
					if (VCWD_CHOWN(url_to, sb.st_uid, sb.st_gid)) {
						if (errno == EPERM) {
							himote_error_docref2(NULL TSRMLS_CC, url_from, url_to, E_WARNING, "%s", strerror(errno));
							VCWD_UNLINK(url_from);
							return 1;
						}
						himote_error_docref2(NULL TSRMLS_CC, url_from, url_to, E_WARNING, "%s", strerror(errno));
						return 0;
					}
#  endif
					VCWD_UNLINK(url_from);
					return 1;
				}
			}
			himote_error_docref2(NULL TSRMLS_CC, url_from, url_to, E_WARNING, "%s", strerror(errno));
			return 0;
		}
# endif
#endif

#ifdef HIMOTE_WIN32
		himote_win32_docref2_from_error(GetLastError(), url_from, url_to TSRMLS_CC);
#else
		himote_error_docref2(NULL TSRMLS_CC, url_from, url_to, E_WARNING, "%s", strerror(errno));
#endif
		return 0;
	}

	/* Clear stat cache (and realpath cache) */
	himote_clear_stat_cache(1, NULL, 0 TSRMLS_CC);

	return 1;
}

static int himote_plain_files_mkdir(himote_stream_wrapper *wrapper, char *dir, int mode, int options, himote_stream_context *context TSRMLS_DC)
{
	int ret, recursive = options & HIMOTE_STREAM_MKDIR_RECURSIVE;
	char *p;

	if ((p = strstr(dir, "://")) != NULL) {
		if (p < strchr(dir, '/')) {
			dir = p + 3;
		}
	}

	if (!recursive) {
		ret = himote_mkdir(dir, mode TSRMLS_CC);
	} else {
		/* we look for directory separator from the end of string, thus hopefuly reducing our work load */
		char *e, *buf;
		struct stat sb;
		int dir_len = strlen(dir);
		int offset = 0;

		buf = estrndup(dir, dir_len);

#ifdef HIMOTE_WIN32
		e = buf;
		while (*e) {
			if (*e == '/') {
				*e = DEFAULT_SLASH;
			}
			e++;
		}
#else
		e = buf + dir_len;
#endif

		if ((p = memchr(buf, DEFAULT_SLASH, dir_len))) {
			offset = p - buf + 1;
		}

		if (p && dir_len == 1) {
			/* buf == "DEFAULT_SLASH" */	
		}
		else {
			/* find a top level directory we need to create */
			while ( (p = strrchr(buf + offset, DEFAULT_SLASH)) || (offset != 1 && (p = strrchr(buf, DEFAULT_SLASH))) ) {
				int n = 0;

				*p = '\0';
				while (p > buf && *(p-1) == DEFAULT_SLASH) {
					++n;
					--p;
					*p = '\0';
				}
				if (VCWD_STAT(buf, &sb) == 0) {
					while (1) {
						*p = DEFAULT_SLASH;
						if (!n) break;
						--n;
						++p;
					}
					break;
				}
			}
		}

		if (p == buf) {
			ret = himote_mkdir(dir, mode TSRMLS_CC);
		} else if (!(ret = himote_mkdir(buf, mode TSRMLS_CC))) {
			if (!p) {
				p = buf;
			}
			/* create any needed directories if the creation of the 1st directory worked */
			while (++p != e) {
				if (*p == '\0') {
					*p = DEFAULT_SLASH;
					if ((*(p+1) != '\0') &&
						(ret = VCWD_MKDIR(buf, (mode_t)mode)) < 0) {
						if (options & REPORT_ERRORS) {
							himote_error_docref(NULL TSRMLS_CC, E_WARNING, "%s", strerror(errno));
						}
						break;
					}
				}
			}
		}
		efree(buf);
	}
	if (ret < 0) {
		/* Failure */
		return 0;
	} else {
		/* Success */
		return 1;
	}
}

static int himote_plain_files_rmdir(himote_stream_wrapper *wrapper, char *url, int options, himote_stream_context *context TSRMLS_DC)
{
#if HIMOTE_WIN32
	int url_len = strlen(url);
#endif
	if (himote_check_open_basedir(url TSRMLS_CC)) {
		return 0;
	}

#if HIMOTE_WIN32
	if (!himote_win32_check_trailing_space(url, url_len)) {
		himote_error_docref1(NULL TSRMLS_CC, url, E_WARNING, "%s", strerror(ENOENT));
		return 0;
	}
#endif

	if (VCWD_RMDIR(url) < 0) {
		himote_error_docref1(NULL TSRMLS_CC, url, E_WARNING, "%s", strerror(errno));
		return 0;
	}

	/* Clear stat cache (and realpath cache) */
	himote_clear_stat_cache(1, NULL, 0 TSRMLS_CC);

	return 1;
}

static himote_stream_wrapper_ops himote_plain_files_wrapper_ops = {
	himote_plain_files_stream_opener,
	NULL,
	NULL,
	himote_plain_files_url_stater,
	himote_plain_files_dir_opener,
	"plainfile",
	himote_plain_files_unlink,
	himote_plain_files_rename,
	himote_plain_files_mkdir,
	himote_plain_files_rmdir
};

himote_stream_wrapper himote_plain_files_wrapper = {
	&himote_plain_files_wrapper_ops,
	NULL,
	0
};

/* {{{ himote_stream_fopen_with_path */
HIMOTEAPI himote_stream *_himote_stream_fopen_with_path(char *filename, char *mode, char *path, char **opened_path, int options STREAMS_DC TSRMLS_DC)
{
	/* code ripped off from fopen_wrappers.c */
	char *pathbuf, *ptr, *end;
	char *exec_fname;
	char trypath[MAXPATHLEN];
	himote_stream *stream;
	int path_length;
	int filename_length;
	int exec_fname_length;

	if (opened_path) {
		*opened_path = NULL;
	}

	if(!filename) {
		return NULL;
	}

	filename_length = strlen(filename);

	/* Relative path open */
	if (*filename == '.' && (IS_SLASH(filename[1]) || filename[1] == '.')) {
		/* further checks, we could have ....... filenames */
		ptr = filename + 1;
		if (*ptr == '.') {
			while (*(++ptr) == '.');
			if (!IS_SLASH(*ptr)) { /* not a relative path after all */
				goto not_relative_path;
			}
		}


		if (((options & STREAM_DISABLE_OPEN_BASEDIR) == 0) && himote_check_open_basedir(filename TSRMLS_CC)) {
			return NULL;
		}

		return himote_stream_fopen_rel(filename, mode, opened_path, options);
	}

	/*
	 * files in safe_mode_include_dir (or subdir) are excluded from
	 * safe mode GID/UID checks
	 */

not_relative_path:

	/* Absolute path open */
	if (IS_ABSOLUTE_PATH(filename, filename_length)) {

		if (((options & STREAM_DISABLE_OPEN_BASEDIR) == 0) && himote_check_open_basedir(filename TSRMLS_CC)) {
			return NULL;
		}

		if ((himote_check_safe_mode_include_dir(filename TSRMLS_CC)) == 0)
			/* filename is in safe_mode_include_dir (or subdir) */
			return himote_stream_fopen_rel(filename, mode, opened_path, options);

		return himote_stream_fopen_rel(filename, mode, opened_path, options);
	}
	
#ifdef HIMOTE_WIN32
	if (IS_SLASH(filename[0])) {
		size_t cwd_len;
		char *cwd;
		cwd = virtual_getcwd_ex(&cwd_len TSRMLS_CC);
		/* getcwd() will return always return [DRIVE_LETTER]:/) on windows. */
		*(cwd+3) = '\0';
	
		if (snprintf(trypath, MAXPATHLEN, "%s%s", cwd, filename) >= MAXPATHLEN) {
			himote_error_docref(NULL TSRMLS_CC, E_NOTICE, "%s/%s path was truncated to %d", cwd, filename, MAXPATHLEN);
		}
		
		free(cwd);
		
		if (((options & STREAM_DISABLE_OPEN_BASEDIR) == 0) && himote_check_open_basedir(trypath TSRMLS_CC)) {
			return NULL;
		}
		if ((himote_check_safe_mode_include_dir(trypath TSRMLS_CC)) == 0) {
			return himote_stream_fopen_rel(trypath, mode, opened_path, options);
		}	
		if (PG(safe_mode) && (!himote_checkuid(trypath, mode, CHECKUID_CHECK_MODE_PARAM))) {
			return NULL;
		}
		
		return himote_stream_fopen_rel(trypath, mode, opened_path, options);
	}
#endif

	if (!path || (path && !*path)) {
		return himote_stream_fopen_rel(filename, mode, opened_path, options);
	}

	/* check in provided path */
	/* append the calling scripts' current working directory
	 * as a fall back case
	 */
	if (zend_is_executing(TSRMLS_C)) {
		exec_fname = zend_get_executed_filename(TSRMLS_C);
		exec_fname_length = strlen(exec_fname);
		path_length = strlen(path);

		while ((--exec_fname_length >= 0) && !IS_SLASH(exec_fname[exec_fname_length]));
		if ((exec_fname && exec_fname[0] == '[')
				|| exec_fname_length<=0) {
			/* [no active file] or no path */
			pathbuf = estrdup(path);
		} else {
			pathbuf = (char *) emalloc(exec_fname_length + path_length +1 +1);
			memcpy(pathbuf, path, path_length);
			pathbuf[path_length] = DEFAULT_DIR_SEPARATOR;
			memcpy(pathbuf+path_length+1, exec_fname, exec_fname_length);
			pathbuf[path_length + exec_fname_length +1] = '\0';
		}
	} else {
		pathbuf = estrdup(path);
	}

	ptr = pathbuf;

	while (ptr && *ptr) {
		end = strchr(ptr, DEFAULT_DIR_SEPARATOR);
		if (end != NULL) {
			*end = '\0';
			end++;
		}
		if (*ptr == '\0') {
			goto stream_skip;
		}
		if (snprintf(trypath, MAXPATHLEN, "%s/%s", ptr, filename) >= MAXPATHLEN) {
			himote_error_docref(NULL TSRMLS_CC, E_NOTICE, "%s/%s path was truncated to %d", ptr, filename, MAXPATHLEN);
		}

		if (((options & STREAM_DISABLE_OPEN_BASEDIR) == 0) && himote_check_open_basedir_ex(trypath, 0 TSRMLS_CC)) {
			goto stream_skip;
		}
		
		if (PG(safe_mode)) {
			struct stat sb;

			if (VCWD_STAT(trypath, &sb) == 0) {
				/* file exists ... check permission */
				if ((himote_check_safe_mode_include_dir(trypath TSRMLS_CC) == 0)) {
					/* UID ok, or trypath is in safe_mode_include_dir */
					stream = himote_stream_fopen_rel(trypath, mode, opened_path, options);
					goto stream_done;
				}
			}
			goto stream_skip;
		}
		stream = himote_stream_fopen_rel(trypath, mode, opened_path, options);
		if (stream) {
stream_done:
			efree(pathbuf);
			return stream;
		}
stream_skip:
		ptr = end;
	} /* end provided path */

	efree(pathbuf);
	return NULL;

}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
