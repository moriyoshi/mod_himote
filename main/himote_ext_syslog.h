/*
   +----------------------------------------------------------------------+
   | HIMOTE Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2012 The HIMOTE Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the HIMOTE license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the HIMOTE license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Stig Sæther Bakken <ssb@php.net>                             |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_EXT_SYSLOG_H
#define HIMOTE_EXT_SYSLOG_H

#ifdef HAVE_SYSLOG_H

#include "himote_syslog.h"

HIMOTE_MINIT_FUNCTION(syslog);
HIMOTE_RINIT_FUNCTION(syslog);
#ifdef HIMOTE_WIN32
HIMOTE_RSHUTDOWN_FUNCTION(syslog);
#endif
HIMOTE_MSHUTDOWN_FUNCTION(syslog);

HIMOTE_FUNCTION(openlog);
HIMOTE_FUNCTION(syslog);
HIMOTE_FUNCTION(closelog);
HIMOTE_FUNCTION(define_syslog_variables);

#endif

#endif /* HIMOTE_EXT_SYSLOG_H */
