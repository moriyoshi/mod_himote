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

HIMOTEAPI extern himote_stream_wrapper  himote_glob_stream_wrapper;
HIMOTEAPI extern himote_stream_ops      himote_glob_stream_ops;

BEGIN_EXTERN_C()

HIMOTEAPI char* _himote_glob_stream_get_path(himote_stream *stream, int copy, int *plen STREAMS_DC TSRMLS_DC);
#define himote_glob_stream_get_path(stream, copy, plen)	_himote_glob_stream_get_path((stream), (copy), (plen) STREAMS_CC TSRMLS_CC)

HIMOTEAPI char* _himote_glob_stream_get_pattern(himote_stream *stream, int copy, int *plen STREAMS_DC TSRMLS_DC);
#define himote_glob_stream_get_pattern(stream, copy, plen)	_himote_glob_stream_get_pattern((stream), (copy), (plen) STREAMS_CC TSRMLS_CC)

HIMOTEAPI int   _himote_glob_stream_get_count(himote_stream *stream, int *pflags STREAMS_DC TSRMLS_DC);
#define himote_glob_stream_get_count(stream, pflags)	_himote_glob_stream_get_count((stream), (pflags) STREAMS_CC TSRMLS_CC)

END_EXTERN_C()

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
