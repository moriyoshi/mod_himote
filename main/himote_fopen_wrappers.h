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
   | Authors: Rasmus Lerdorf <rasmus@php.net>                             |
   |          Jim Winstead <jimw@php.net>                                 |
   |          Hartmut Holzgraefe <hholzgra@php.net>                       |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_FOPEN_WRAPPERS_H
#define HIMOTE_FOPEN_WRAPPERS_H

himote_stream *himote_stream_url_wrap_http(himote_stream_wrapper *wrapper, char *path, char *mode, int options, char **opened_path, himote_stream_context *context STREAMS_DC TSRMLS_DC);
himote_stream *himote_stream_url_wrap_ftp(himote_stream_wrapper *wrapper, char *path, char *mode, int options, char **opened_path, himote_stream_context *context STREAMS_DC TSRMLS_DC);
extern HIMOTEAPI himote_stream_wrapper himote_stream_http_wrapper;
extern HIMOTEAPI himote_stream_wrapper himote_stream_ftp_wrapper;
extern himote_stream_wrapper himote_stream_himote_wrapper;
extern himote_stream_wrapper himote_plain_files_wrapper;

#endif
