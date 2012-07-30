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

/* Memory Mapping interface for streams */
#include "himote.h"
#include "himote_streams_int.h"

HIMOTEAPI char *_himote_stream_mmap_range(himote_stream *stream, size_t offset, size_t length, himote_stream_mmap_operation_t mode, size_t *mapped_len TSRMLS_DC)
{
	himote_stream_mmap_range range;
	
	range.offset = offset;
	range.length = length;
	range.mode = mode;
	range.mapped = NULL;

	/* For now, we impose an arbitrary limit to avoid
	 * runaway swapping when large files are passed thru. */
	if (length > 4 * 1024 * 1024) {
		return NULL;
	}
	
	if (HIMOTE_STREAM_OPTION_RETURN_OK == himote_stream_set_option(stream, HIMOTE_STREAM_OPTION_MMAP_API, HIMOTE_STREAM_MMAP_MAP_RANGE, &range)) {
		if (mapped_len) {
			*mapped_len = range.length;
		}
		return range.mapped;
	}
	return NULL;
}

HIMOTEAPI int _himote_stream_mmap_unmap(himote_stream *stream TSRMLS_DC)
{
	return himote_stream_set_option(stream, HIMOTE_STREAM_OPTION_MMAP_API, HIMOTE_STREAM_MMAP_UNMAP, NULL) == HIMOTE_STREAM_OPTION_RETURN_OK ? 1 : 0;
}

HIMOTEAPI int _himote_stream_mmap_unmap_ex(himote_stream *stream, off_t readden TSRMLS_DC)
{
	int ret = 1;

	if (himote_stream_seek(stream, readden, SEEK_CUR) != 0) {
		ret = 0;
	}
	if (himote_stream_mmap_unmap(stream) == 0) {
		ret = 0;
	}

	return ret;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
