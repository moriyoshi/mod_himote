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
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_SYSLOG_H
#define HIMOTE_SYSLOG_H

#ifdef HIMOTE_WIN32
#include "win32/syslog.h"
#else
#include <himote_config.h>
#ifdef HAVE_SYSLOG_H
#include <syslog.h>
#endif
#endif

/* 
 * The SCO OpenServer 5 Development System (not the UDK)
 * defines syslog to std_syslog.
 */

#ifdef syslog

#ifdef HAVE_STD_SYSLOG
#define himote_syslog std_syslog
#endif

#undef syslog

#endif

#ifndef himote_syslog
#define himote_syslog syslog
#endif

#endif
