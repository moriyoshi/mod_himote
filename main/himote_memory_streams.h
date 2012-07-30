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
   | Author: Marcus Boerger <helly@php.net>                               |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#ifndef HIMOTE_MEMORY_STREAM_H
#define HIMOTE_MEMORY_STREAM_H

#include "himote_streams.h"

#define HIMOTE_STREAM_MAX_MEM	2 * 1024 * 1024

#define TEMP_STREAM_DEFAULT  0
#define TEMP_STREAM_READONLY 1
#define TEMP_STREAM_TAKE_BUFFER 2

#define himote_stream_memory_create(mode) _himote_stream_memory_create((mode) STREAMS_CC TSRMLS_CC)
#define himote_stream_memory_create_rel(mode) _himote_stream_memory_create((mode) STREAMS_REL_CC TSRMLS_CC)
#define himote_stream_memory_open(mode, buf, length) _himote_stream_memory_open((mode), (buf), (length) STREAMS_CC TSRMLS_CC)
#define himote_stream_memory_get_buffer(stream, length) _himote_stream_memory_get_buffer((stream), (length) STREAMS_CC TSRMLS_CC)

#define himote_stream_temp_new() himote_stream_temp_create(TEMP_STREAM_DEFAULT, HIMOTE_STREAM_MAX_MEM)
#define himote_stream_temp_create(mode, max_memory_usage) _himote_stream_temp_create((mode), (max_memory_usage) STREAMS_CC TSRMLS_CC)
#define himote_stream_temp_create_rel(mode, max_memory_usage) _himote_stream_temp_create((mode), (max_memory_usage) STREAMS_REL_CC TSRMLS_CC)
#define himote_stream_temp_open(mode, max_memory_usage, buf, length) _himote_stream_temp_open((mode), (max_memory_usage), (buf), (length) STREAMS_CC TSRMLS_CC)

BEGIN_EXTERN_C()
HIMOTEAPI himote_stream *_himote_stream_memory_create(int mode STREAMS_DC TSRMLS_DC);
HIMOTEAPI himote_stream *_himote_stream_memory_open(int mode, char *buf, size_t length STREAMS_DC TSRMLS_DC);
HIMOTEAPI char *_himote_stream_memory_get_buffer(himote_stream *stream, size_t *length STREAMS_DC TSRMLS_DC);

HIMOTEAPI himote_stream *_himote_stream_temp_create(int mode, size_t max_memory_usage STREAMS_DC TSRMLS_DC);
HIMOTEAPI himote_stream *_himote_stream_temp_open(int mode, size_t max_memory_usage, char *buf, size_t length STREAMS_DC TSRMLS_DC);
END_EXTERN_C()

extern HIMOTEAPI himote_stream_ops himote_stream_memory_ops;
extern HIMOTEAPI himote_stream_ops himote_stream_temp_ops;
extern HIMOTEAPI himote_stream_ops himote_stream_rfc2397_ops;
extern HIMOTEAPI himote_stream_wrapper himote_stream_rfc2397_wrapper;

#define HIMOTE_STREAM_IS_MEMORY &himote_stream_memory_ops
#define HIMOTE_STREAM_IS_TEMP   &himote_stream_temp_ops

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
