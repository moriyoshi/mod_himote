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
   | Author: Thies C. Arntzen <thies@thieso.net>                          |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#ifndef HIMOTE_DIR_H
#define HIMOTE_DIR_H

/* directory functions */
HIMOTE_MINIT_FUNCTION(dir);
HIMOTE_RINIT_FUNCTION(dir);
HIMOTE_FUNCTION(opendir);
HIMOTE_FUNCTION(closedir);
HIMOTE_FUNCTION(chdir);
#if defined(HAVE_CHROOT) && !defined(ZTS) && ENABLE_CHROOT_FUNC
HIMOTE_FUNCTION(chroot);
#endif
HIMOTE_FUNCTION(getcwd);
HIMOTE_FUNCTION(rewinddir);
HIMOTE_NAMED_FUNCTION(himote_if_readdir);
HIMOTE_FUNCTION(getdir);
HIMOTE_FUNCTION(glob);
HIMOTE_FUNCTION(scandir);

#endif /* HIMOTE_DIR_H */
