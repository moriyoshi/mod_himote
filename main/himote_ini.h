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

#ifndef HIMOTE_INI_H
#define HIMOTE_INI_H

#include "zend_ini.h"

BEGIN_EXTERN_C()
HIMOTEAPI void config_zval_dtor(zval *zvalue);
int himote_init_config(TSRMLS_D);
int himote_shutdown_config(void);
void himote_ini_register_extensions(TSRMLS_D);
HIMOTEAPI zval *cfg_get_entry(const char *name, uint name_length);
HIMOTEAPI int cfg_get_long(const char *varname, long *result);
HIMOTEAPI int cfg_get_double(const char *varname, double *result);
HIMOTEAPI int cfg_get_string(const char *varname, char **result);
HIMOTEAPI int himote_parse_user_ini_file(const char *dirname, char *ini_filename, HashTable *target_hash TSRMLS_DC);
HIMOTEAPI void himote_ini_activate_config(HashTable *source_hash, int modify_type, int stage TSRMLS_DC);
HIMOTEAPI int himote_ini_has_per_dir_config(void);
HIMOTEAPI int himote_ini_has_per_host_config(void);
HIMOTEAPI void himote_ini_activate_per_dir_config(char *path, uint path_len TSRMLS_DC);
HIMOTEAPI void himote_ini_activate_per_host_config(const char *host, uint host_len TSRMLS_DC);
HIMOTEAPI HashTable* himote_ini_get_configuration_hash(void);
END_EXTERN_C()

#define HIMOTE_INI_USER	ZEND_INI_USER
#define HIMOTE_INI_PERDIR	ZEND_INI_PERDIR
#define HIMOTE_INI_SYSTEM	ZEND_INI_SYSTEM

#define HIMOTE_INI_ALL 	ZEND_INI_ALL

#define himote_ini_entry	zend_ini_entry

#define HIMOTE_INI_MH		ZEND_INI_MH
#define HIMOTE_INI_DISP	ZEND_INI_DISP

#define HIMOTE_INI_BEGIN		ZEND_INI_BEGIN
#define HIMOTE_INI_END			ZEND_INI_END

#define HIMOTE_INI_ENTRY3_EX	ZEND_INI_ENTRY3_EX
#define HIMOTE_INI_ENTRY3		ZEND_INI_ENTRY3
#define HIMOTE_INI_ENTRY2_EX	ZEND_INI_ENTRY2_EX
#define HIMOTE_INI_ENTRY2		ZEND_INI_ENTRY2
#define HIMOTE_INI_ENTRY1_EX	ZEND_INI_ENTRY1_EX
#define HIMOTE_INI_ENTRY1		ZEND_INI_ENTRY1
#define HIMOTE_INI_ENTRY_EX	ZEND_INI_ENTRY_EX
#define HIMOTE_INI_ENTRY		ZEND_INI_ENTRY

#define STD_HIMOTE_INI_ENTRY		STD_ZEND_INI_ENTRY
#define STD_HIMOTE_INI_ENTRY_EX	STD_ZEND_INI_ENTRY_EX
#define STD_HIMOTE_INI_BOOLEAN		STD_ZEND_INI_BOOLEAN

#define HIMOTE_INI_DISPLAY_ORIG	ZEND_INI_DISPLAY_ORIG
#define HIMOTE_INI_DISPLAY_ACTIVE	ZEND_INI_DISPLAY_ACTIVE

#define HIMOTE_INI_STAGE_STARTUP		ZEND_INI_STAGE_STARTUP
#define HIMOTE_INI_STAGE_SHUTDOWN		ZEND_INI_STAGE_SHUTDOWN
#define HIMOTE_INI_STAGE_ACTIVATE		ZEND_INI_STAGE_ACTIVATE
#define HIMOTE_INI_STAGE_DEACTIVATE	ZEND_INI_STAGE_DEACTIVATE
#define HIMOTE_INI_STAGE_RUNTIME		ZEND_INI_STAGE_RUNTIME
#define HIMOTE_INI_STAGE_HTACCESS		ZEND_INI_STAGE_HTACCESS

#define himote_ini_boolean_displayer_cb	zend_ini_boolean_displayer_cb
#define himote_ini_color_displayer_cb		zend_ini_color_displayer_cb

#define himote_alter_ini_entry		zend_alter_ini_entry

#define himote_ini_long	zend_ini_long
#define himote_ini_double	zend_ini_double
#define himote_ini_string	zend_ini_string

#endif /* HIMOTE_INI_H */
