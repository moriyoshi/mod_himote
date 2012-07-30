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
   | Author: Zeev Suraski <zeev@zend.com>                                 |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_OPEN_TEMPORARY_FILE_H
#define HIMOTE_OPEN_TEMPORARY_FILE_H

BEGIN_EXTERN_C()
HIMOTEAPI FILE *himote_open_temporary_file(const char *dir, const char *pfx, char **opened_path_p TSRMLS_DC);
HIMOTEAPI int himote_open_temporary_fd_ex(const char *dir, const char *pfx, char **opened_path_p, zend_bool open_basedir_check TSRMLS_DC);
HIMOTEAPI int himote_open_temporary_fd(const char *dir, const char *pfx, char **opened_path_p TSRMLS_DC);
HIMOTEAPI const char *himote_get_temporary_directory(void);
HIMOTEAPI void himote_shutdown_temporary_directory(void);
END_EXTERN_C()

#endif /* HIMOTE_OPEN_TEMPORARY_FILE_H */
