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
  | Author: Wez Furlong <wez@thebrainroom.com>                           |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

/* Memory Mapping interface for streams.
 * The intention is to provide a uniform interface over the most common
 * operations that are used within HIMOTE itself, rather than a complete
 * API for all memory mapping needs.
 *
 * ATM, we support only mmap(), but win32 memory mapping support will
 * follow soon.
 * */

typedef enum {
	/* Does the stream support mmap ? */
	HIMOTE_STREAM_MMAP_SUPPORTED,
	/* Request a range and offset to be mapped;
	 * while mapped, you MUST NOT use any read/write functions
	 * on the stream (win9x compatibility) */
	HIMOTE_STREAM_MMAP_MAP_RANGE,
	/* Unmap the last range that was mapped for the stream */
	HIMOTE_STREAM_MMAP_UNMAP
} himote_stream_mmap_operation_t;
	
typedef enum {
	HIMOTE_STREAM_MAP_MODE_READONLY,
	HIMOTE_STREAM_MAP_MODE_READWRITE,
	HIMOTE_STREAM_MAP_MODE_SHARED_READONLY,
	HIMOTE_STREAM_MAP_MODE_SHARED_READWRITE
} himote_stream_mmap_access_t;

typedef struct {
	/* requested offset and length.
	 * If length is 0, the whole file is mapped */
	size_t offset;
	size_t length;
	
	himote_stream_mmap_access_t mode;
	
	/* returned mapped address */
	char *mapped;

} himote_stream_mmap_range;

#define HIMOTE_STREAM_MMAP_ALL 0

#define himote_stream_mmap_supported(stream)	(_himote_stream_set_option((stream), HIMOTE_STREAM_OPTION_MMAP_API, HIMOTE_STREAM_MMAP_SUPPORTED, NULL TSRMLS_CC) == 0 ? 1 : 0)

/* Returns 1 if the stream in its current state can be memory mapped,
 * 0 otherwise */
#define himote_stream_mmap_possible(stream)			(!himote_stream_is_filtered((stream)) && himote_stream_mmap_supported((stream)))

BEGIN_EXTERN_C()
HIMOTEAPI char *_himote_stream_mmap_range(himote_stream *stream, size_t offset, size_t length, himote_stream_mmap_operation_t mode, size_t *mapped_len TSRMLS_DC);
#define himote_stream_mmap_range(stream, offset, length, mode, mapped_len)	_himote_stream_mmap_range((stream), (offset), (length), (mode), (mapped_len) TSRMLS_CC)

/* un-maps the last mapped range */
HIMOTEAPI int _himote_stream_mmap_unmap(himote_stream *stream TSRMLS_DC);
#define himote_stream_mmap_unmap(stream)				_himote_stream_mmap_unmap((stream) TSRMLS_CC)

HIMOTEAPI int _himote_stream_mmap_unmap_ex(himote_stream *stream, off_t readden TSRMLS_DC);
#define himote_stream_mmap_unmap_ex(stream, readden)			_himote_stream_mmap_unmap_ex((stream), (readden) TSRMLS_CC)
END_EXTERN_C()

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
