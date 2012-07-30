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
   | Authors: Brian Schaffner <brian@tool.net>                            |
   |          Shane Caraveo <shane@caraveo.com>                           |
   |          Zeev Suraski <zeev@zend.com>                                |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_DL_H
#define HIMOTE_DL_H

HIMOTEAPI int himote_load_extension(char *filename, int type, int start_now TSRMLS_DC);
HIMOTEAPI void himote_dl(char *file, int type, zval *return_value, int start_now TSRMLS_DC);

/* dynamic loading functions */
HIMOTEAPI HIMOTE_FUNCTION(dl);

HIMOTE_MINFO_FUNCTION(dl);

#endif /* HIMOTE_DL_H */
