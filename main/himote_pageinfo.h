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
   | Author: Jim Winstead <jimw@php.net>                                  |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PAGEINFO_H
#define PAGEINFO_H

HIMOTE_FUNCTION(getmyuid);
HIMOTE_FUNCTION(getmygid);
HIMOTE_FUNCTION(getmypid);
HIMOTE_FUNCTION(getmyinode);
HIMOTE_FUNCTION(getlastmod);

HIMOTEAPI void himote_statpage(TSRMLS_D);
HIMOTEAPI long himote_getlastmod(TSRMLS_D);
extern long himote_getuid(void);
extern long himote_getgid(void);

#endif
