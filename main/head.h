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
   | Author: Rasmus Lerdorf <rasmus@lerdorf.on.ca>                        |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HEAD_H
#define HEAD_H

extern HIMOTE_RINIT_FUNCTION(head);
HIMOTE_FUNCTION(header);
HIMOTE_FUNCTION(header_remove);
HIMOTE_FUNCTION(setcookie);
HIMOTE_FUNCTION(setrawcookie);
HIMOTE_FUNCTION(headers_sent);
HIMOTE_FUNCTION(headers_list);

HIMOTEAPI int himote_header(TSRMLS_D);
HIMOTEAPI int himote_setcookie(char *name, int name_len, char *value, int value_len, time_t expires, char *path, int path_len, char *domain, int domain_len, int secure, int url_encode, int httponly TSRMLS_DC);

#endif
