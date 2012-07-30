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

#ifndef FOPEN_WRAPPERS_H
#define FOPEN_WRAPPERS_H

BEGIN_EXTERN_C()
#include "himote_globals.h"
#include "himote_ini.h"

HIMOTEAPI int himote_fopen_primary_script(zend_file_handle *file_handle TSRMLS_DC);
HIMOTEAPI char *expand_filepath(const char *filepath, char *real_path TSRMLS_DC);
HIMOTEAPI char *expand_filepath_ex(const char *filepath, char *real_path, const char *relative_to, size_t relative_to_len TSRMLS_DC);

HIMOTEAPI int himote_check_open_basedir(const char *path TSRMLS_DC);
HIMOTEAPI int himote_check_open_basedir_ex(const char *path, int warn TSRMLS_DC);
HIMOTEAPI int himote_check_specific_open_basedir(const char *basedir, const char *path TSRMLS_DC);

/* {{{ OPENBASEDIR_CHECKPATH(filename) to ease merge between 6.x and 5.x */
#if (HIMOTE_MAJOR_VERSION < 6)
# define OPENBASEDIR_CHECKPATH(filename) \
	(PG(safe_mode) && (!himote_checkuid(filename, NULL, CHECKUID_CHECK_FILE_AND_DIR))) || himote_check_open_basedir(filename TSRMLS_CC)
#else
#define OPENBASEDIR_CHECKPATH(filename) \
	himote_check_open_basedir(filename TSRMLS_CC)
#endif
/* }}} */

HIMOTEAPI int himote_check_safe_mode_include_dir(const char *path TSRMLS_DC);

HIMOTEAPI char *himote_resolve_path(const char *filename, int filename_len, const char *path TSRMLS_DC);

HIMOTEAPI FILE *himote_fopen_with_path(const char *filename, const char *mode, const char *path, char **opened_path TSRMLS_DC);

HIMOTEAPI char *himote_strip_url_passwd(char *path);

HIMOTEAPI ZEND_INI_MH(OnUpdateBaseDir);
END_EXTERN_C()

#endif
/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
