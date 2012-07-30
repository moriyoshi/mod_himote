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
   | Author: Jaakko Hyv�tti <jaakko.hyvatti@iki.fi>                       |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#include <stdio.h>
#include <stdarg.h>
#include "himote.h"
#ifdef HIMOTE_WIN32
#include "config.w32.h"
#else
#include <himote_config.h>
#endif

HIMOTEAPI int
himote_sprintf (char*s, const char* format, ...)
{
  va_list args;
  int ret;

  va_start (args, format);
  s[0] = '\0';
  ret = vsprintf (s, format, args);
  va_end (args);
  return (ret < 0) ? -1 : ret;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
