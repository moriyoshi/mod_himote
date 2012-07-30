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
   | Author:                                                              |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_LINK_H
#define HIMOTE_LINK_H

#if defined(HAVE_SYMLINK) || defined(HIMOTE_WIN32)

HIMOTE_FUNCTION(link);
HIMOTE_FUNCTION(readlink);
HIMOTE_FUNCTION(linkinfo);
HIMOTE_FUNCTION(symlink);

#endif

#endif /* HIMOTE_LINK_H */
