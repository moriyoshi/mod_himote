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

#define _GNU_SOURCE
#include "himote.h"
#include "himote_globals.h"
#include "himote_network.h"
#include "himote_open_temporary_file.h"
#include "himote_file.h"
#include <stddef.h>
#include <fcntl.h>

#include "himote_streams_int.h"

/* Under BSD, emulate fopencookie using funopen */
#if defined(HAVE_FUNOPEN) && !defined(HAVE_FOPENCOOKIE)
typedef struct {
	int (*reader)(void *, char *, int);
	int (*writer)(void *, const char *, int);
	fpos_t (*seeker)(void *, fpos_t, int);
	int (*closer)(void *);
} COOKIE_IO_FUNCTIONS_T;

FILE *fopencookie(void *cookie, const char *mode, COOKIE_IO_FUNCTIONS_T *funcs)
{
	return funopen(cookie, funcs->reader, funcs->writer, funcs->seeker, funcs->closer);
}
# define HAVE_FOPENCOOKIE 1
# define HIMOTE_EMULATE_FOPENCOOKIE 1
# define HIMOTE_STREAM_COOKIE_FUNCTIONS	&stream_cookie_functions
#elif defined(HAVE_FOPENCOOKIE)
# define HIMOTE_STREAM_COOKIE_FUNCTIONS	stream_cookie_functions
#endif

/* {{{ STDIO with fopencookie */
#if defined(HIMOTE_EMULATE_FOPENCOOKIE)
/* use our fopencookie emulation */
static int stream_cookie_reader(void *cookie, char *buffer, int size)
{
	int ret;
	TSRMLS_FETCH();

	ret = himote_stream_read((himote_stream*)cookie, buffer, size);
	return ret;
}

static int stream_cookie_writer(void *cookie, const char *buffer, int size)
{
	TSRMLS_FETCH();

	return himote_stream_write((himote_stream *)cookie, (char *)buffer, size);
}

static fpos_t stream_cookie_seeker(void *cookie, off_t position, int whence)
{
	TSRMLS_FETCH();

	return (fpos_t)himote_stream_seek((himote_stream *)cookie, position, whence);
}

static int stream_cookie_closer(void *cookie)
{
	himote_stream *stream = (himote_stream*)cookie;
	TSRMLS_FETCH();

	/* prevent recursion */
	stream->fclose_stdiocast = HIMOTE_STREAM_FCLOSE_NONE;
	return himote_stream_close(stream);
}
#elif defined(HAVE_FOPENCOOKIE)
static ssize_t stream_cookie_reader(void *cookie, char *buffer, size_t size)
{
	ssize_t ret;
	TSRMLS_FETCH();

	ret = himote_stream_read(((himote_stream *)cookie), buffer, size);
	return ret;
}

static ssize_t stream_cookie_writer(void *cookie, const char *buffer, size_t size)
{
	TSRMLS_FETCH();

	return himote_stream_write(((himote_stream *)cookie), (char *)buffer, size);
}

# ifdef COOKIE_SEEKER_USES_OFF64_T
static int stream_cookie_seeker(void *cookie, __off64_t *position, int whence)
{
	TSRMLS_FETCH();

	*position = himote_stream_seek((himote_stream *)cookie, (off_t)*position, whence);

	if (*position == -1) {
		return -1;
	}
	return 0;
}
# else
static int stream_cookie_seeker(void *cookie, off_t position, int whence)
{
	TSRMLS_FETCH();

	return himote_stream_seek((himote_stream *)cookie, position, whence);
}
# endif

static int stream_cookie_closer(void *cookie)
{
	himote_stream *stream = (himote_stream*)cookie;
	TSRMLS_FETCH();

	/* prevent recursion */
	stream->fclose_stdiocast = HIMOTE_STREAM_FCLOSE_NONE;
	return himote_stream_close(stream);
}
#endif /* elif defined(HAVE_FOPENCOOKIE) */

#if HAVE_FOPENCOOKIE
static COOKIE_IO_FUNCTIONS_T stream_cookie_functions =
{
	stream_cookie_reader, stream_cookie_writer,
	stream_cookie_seeker, stream_cookie_closer
};
#else
/* TODO: use socketpair() to emulate fopencookie, as suggested by Hartmut ? */
#endif
/* }}} */

/* {{{ himote_stream_mode_sanitize_fdopen_fopencookie
 * Result should have at least size 5, e.g. to write wbx+\0 */
void himote_stream_mode_sanitize_fdopen_fopencookie(himote_stream *stream, char *result)
{
	/* replace modes not supported by fdopen and fopencookie, but supported 
	 * by HIMOTE's fread(), so that their calls won't fail */
	const char *cur_mode = stream->mode;
	int         has_plus = 0,
		        has_bin  = 0,
				i,
				res_curs = 0;

	if (cur_mode[0] == 'r' || cur_mode[0] == 'w' || cur_mode[0] == 'a') {
		result[res_curs++] = cur_mode[0];
	} else {
		/* assume cur_mode[0] is 'c' or 'x'; substitute by 'w', which should not
		 * truncate anything in fdopen/fopencookie */
		result[res_curs++] = 'w';

		/* x is allowed (at least by glibc & compat), but not as the 1st mode
		 * as in HIMOTE and in any case is (at best) ignored by fdopen and fopencookie */
	}
	
	/* assume current mode has at most length 4 (e.g. wbn+) */
	for (i = 1; i < 4 && cur_mode[i] != '\0'; i++) {
		if (cur_mode[i] == 'b') {
			has_bin = 1;
		} else if (cur_mode[i] == '+') {
			has_plus = 1;
		}
		/* ignore 'n', 't' or other stuff */
	}

	if (has_bin) {
		result[res_curs++] = 'b';
	}
	if (has_plus) {
		result[res_curs++] = '+';
	}

	result[res_curs] = '\0';
}
/* }}} */

/* {{{ himote_stream_cast */
HIMOTEAPI int _himote_stream_cast(himote_stream *stream, int castas, void **ret, int show_err TSRMLS_DC)
{
	int flags = castas & HIMOTE_STREAM_CAST_MASK;
	castas &= ~HIMOTE_STREAM_CAST_MASK;

	/* synchronize our buffer (if possible) */
	if (ret && castas != HIMOTE_STREAM_AS_FD_FOR_SELECT) {
		himote_stream_flush(stream);
		if (stream->ops->seek && (stream->flags & HIMOTE_STREAM_FLAG_NO_SEEK) == 0) {
			off_t dummy;

			stream->ops->seek(stream, stream->position, SEEK_SET, &dummy TSRMLS_CC);
			stream->readpos = stream->writepos = 0;
		}
	}

	/* filtered streams can only be cast as stdio, and only when fopencookie is present */

	if (castas == HIMOTE_STREAM_AS_STDIO) {
		if (stream->stdiocast) {
			if (ret) {
				*(FILE**)ret = stream->stdiocast;
			}
			goto exit_success;
		}

		/* if the stream is a stdio stream let's give it a chance to respond
		 * first, to avoid doubling up the layers of stdio with an fopencookie */
		if (himote_stream_is(stream, HIMOTE_STREAM_IS_STDIO) &&
			stream->ops->cast &&
			!himote_stream_is_filtered(stream) &&
			stream->ops->cast(stream, castas, ret TSRMLS_CC) == SUCCESS
		) {
			goto exit_success;
		}

#if HAVE_FOPENCOOKIE
		/* if just checking, say yes we can be a FILE*, but don't actually create it yet */
		if (ret == NULL) {
			goto exit_success;
		}

		{
			char fixed_mode[5];
			himote_stream_mode_sanitize_fdopen_fopencookie(stream, fixed_mode);
			*(FILE**)ret = fopencookie(stream, fixed_mode, HIMOTE_STREAM_COOKIE_FUNCTIONS);
		}

		if (*ret != NULL) {
			off_t pos;

			stream->fclose_stdiocast = HIMOTE_STREAM_FCLOSE_FOPENCOOKIE;

			/* If the stream position is not at the start, we need to force
			 * the stdio layer to believe it's real location. */
			pos = himote_stream_tell(stream);
			if (pos > 0) {
				fseek(*ret, pos, SEEK_SET);
			}

			goto exit_success;
		}

		/* must be either:
			a) programmer error
			b) no memory
			-> lets bail
		*/
		himote_error_docref(NULL TSRMLS_CC, E_ERROR, "fopencookie failed");
		return FAILURE;
#endif

		if (!himote_stream_is_filtered(stream) && stream->ops->cast && stream->ops->cast(stream, castas, NULL TSRMLS_CC) == SUCCESS) {
			if (FAILURE == stream->ops->cast(stream, castas, ret TSRMLS_CC)) {
				return FAILURE;
			}
			goto exit_success;
		} else if (flags & HIMOTE_STREAM_CAST_TRY_HARD) {
			himote_stream *newstream;

			newstream = himote_stream_fopen_tmpfile();
			if (newstream) {
				size_t retcopy = himote_stream_copy_to_stream_ex(stream, newstream, HIMOTE_STREAM_COPY_ALL, NULL);

				if (retcopy != SUCCESS) {
					himote_stream_close(newstream);
				} else {
					int retcast = himote_stream_cast(newstream, castas | flags, (void **)ret, show_err);

					if (retcast == SUCCESS) {
						rewind(*(FILE**)ret);
					}

					/* do some specialized cleanup */
					if ((flags & HIMOTE_STREAM_CAST_RELEASE)) {
						himote_stream_free(stream, HIMOTE_STREAM_FREE_CLOSE_CASTED);
					}

					/* TODO: we probably should be setting .stdiocast and .fclose_stdiocast or
					 * we may be leaking the FILE*. Needs investigation, though. */
					return retcast;
				}
			}
		}
	}

	if (himote_stream_is_filtered(stream)) {
		himote_error_docref(NULL TSRMLS_CC, E_WARNING, "cannot cast a filtered stream on this system");
		return FAILURE;
	} else if (stream->ops->cast && stream->ops->cast(stream, castas, ret TSRMLS_CC) == SUCCESS) {
		goto exit_success;
	}

	if (show_err) {
		/* these names depend on the values of the HIMOTE_STREAM_AS_XXX defines in himote_streams.h */
		static const char *cast_names[4] = {
			"STDIO FILE*",
			"File Descriptor",
			"Socket Descriptor",
			"select()able descriptor"
		};

		himote_error_docref(NULL TSRMLS_CC, E_WARNING, "cannot represent a stream of type %s as a %s", stream->ops->label, cast_names[castas]);
	}

	return FAILURE;

exit_success:

	if ((stream->writepos - stream->readpos) > 0 &&
		stream->fclose_stdiocast != HIMOTE_STREAM_FCLOSE_FOPENCOOKIE &&
		(flags & HIMOTE_STREAM_CAST_INTERNAL) == 0
	) {
		/* the data we have buffered will be lost to the third party library that
		 * will be accessing the stream.  Emit a warning so that the end-user will
		 * know that they should try something else */

		himote_error_docref(NULL TSRMLS_CC, E_WARNING, "%ld bytes of buffered data lost during stream conversion!", (long)(stream->writepos - stream->readpos));
	}

	if (castas == HIMOTE_STREAM_AS_STDIO && ret) {
		stream->stdiocast = *(FILE**)ret;
	}

	if (flags & HIMOTE_STREAM_CAST_RELEASE) {
		himote_stream_free(stream, HIMOTE_STREAM_FREE_CLOSE_CASTED);
	}

	return SUCCESS;

}
/* }}} */

/* {{{ himote_stream_open_wrapper_as_file */
HIMOTEAPI FILE * _himote_stream_open_wrapper_as_file(char *path, char *mode, int options, char **opened_path STREAMS_DC TSRMLS_DC)
{
	FILE *fp = NULL;
	himote_stream *stream = NULL;

	stream = himote_stream_open_wrapper_rel(path, mode, options|STREAM_WILL_CAST, opened_path);

	if (stream == NULL) {
		return NULL;
	}

	if (himote_stream_cast(stream, HIMOTE_STREAM_AS_STDIO|HIMOTE_STREAM_CAST_TRY_HARD|HIMOTE_STREAM_CAST_RELEASE, (void**)&fp, REPORT_ERRORS) == FAILURE) {
		himote_stream_close(stream);
		if (opened_path && *opened_path) {
			efree(*opened_path);
		}
		return NULL;
	}
	return fp;
}
/* }}} */

/* {{{ himote_stream_make_seekable */
HIMOTEAPI int _himote_stream_make_seekable(himote_stream *origstream, himote_stream **newstream, int flags STREAMS_DC TSRMLS_DC)
{
	if (newstream == NULL) {
		return HIMOTE_STREAM_FAILED;
	}
	*newstream = NULL;

	if (((flags & HIMOTE_STREAM_FORCE_CONVERSION) == 0) && origstream->ops->seek != NULL) {
		*newstream = origstream;
		return HIMOTE_STREAM_UNCHANGED;
	}

	/* Use a tmpfile and copy the old streams contents into it */

	if (flags & HIMOTE_STREAM_PREFER_STDIO) {
		*newstream = himote_stream_fopen_tmpfile();
	} else {
		*newstream = himote_stream_temp_new();
	}

	if (*newstream == NULL) {
		return HIMOTE_STREAM_FAILED;
	}

#if ZEND_DEBUG
	(*newstream)->open_filename = origstream->open_filename;
	(*newstream)->open_lineno = origstream->open_lineno;
#endif

	if (himote_stream_copy_to_stream_ex(origstream, *newstream, HIMOTE_STREAM_COPY_ALL, NULL) != SUCCESS) {
		himote_stream_close(*newstream);
		*newstream = NULL;
		return HIMOTE_STREAM_CRITICAL;
	}

	himote_stream_close(origstream);
	himote_stream_seek(*newstream, 0, SEEK_SET);

	return HIMOTE_STREAM_RELEASED;
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
