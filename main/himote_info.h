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
   | Authors: Rasmus Lerdorf <rasmus@php.net>                             |
   |          Zeev Suraski <zeev@zend.com>                                |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_INFO_H
#define HIMOTE_INFO_H

#define HIMOTE_ENTRY_NAME_COLOR "#ccccff"
#define HIMOTE_CONTENTS_COLOR "#cccccc"
#define HIMOTE_HEADER_COLOR "#9999cc"

#define HIMOTE_INFO_GENERAL			(1<<0)
#define HIMOTE_INFO_CREDITS			(1<<1)
#define HIMOTE_INFO_CONFIGURATION		(1<<2)
#define HIMOTE_INFO_MODULES			(1<<3)
#define HIMOTE_INFO_ENVIRONMENT		(1<<4)
#define HIMOTE_INFO_VARIABLES			(1<<5)
#define HIMOTE_INFO_LICENSE			(1<<6)
#define HIMOTE_INFO_ALL				0xFFFFFFFF

#ifndef HAVE_CREDITS_DEFS
#define HAVE_CREDITS_DEFS

#define HIMOTE_CREDITS_GROUP			(1<<0)
#define HIMOTE_CREDITS_GENERAL			(1<<1)
#define HIMOTE_CREDITS_SAPI			(1<<2)
#define HIMOTE_CREDITS_MODULES			(1<<3)
#define HIMOTE_CREDITS_DOCS			(1<<4)
#define HIMOTE_CREDITS_FULLPAGE		(1<<5)
#define HIMOTE_CREDITS_QA				(1<<6)
#define HIMOTE_CREDITS_WEB             (1<<7)
#define HIMOTE_CREDITS_ALL				0xFFFFFFFF

#endif /* HAVE_CREDITS_DEFS */

#define HIMOTE_LOGO_GUID		  "HIMOTEE9568F34-D428-11d2-A769-00AA001ACF42"
#define HIMOTE_EGG_LOGO_GUID	"HIMOTEE9568F36-D428-11d2-A769-00AA001ACF42"
#define ZEND_LOGO_GUID		"HIMOTEE9568F35-D428-11d2-A769-00AA001ACF42"
#define HIMOTE_CREDITS_GUID  "HIMOTEB8B5F2A0-3C92-11d3-A3A9-4C7B08C10000"

BEGIN_EXTERN_C()
HIMOTE_FUNCTION(himoteversion);
HIMOTE_FUNCTION(himoteinfo);
HIMOTE_FUNCTION(himotecredits);
HIMOTE_FUNCTION(himote_logo_guid);
HIMOTE_FUNCTION(himote_real_logo_guid);
HIMOTE_FUNCTION(zend_logo_guid);
HIMOTE_FUNCTION(himote_egg_logo_guid);
HIMOTE_FUNCTION(himote_sapi_name);
HIMOTE_FUNCTION(himote_uname);
HIMOTE_FUNCTION(himote_ini_scanned_files);
HIMOTE_FUNCTION(himote_ini_loaded_file);
HIMOTEAPI char *himote_info_html_esc(char *string TSRMLS_DC);
HIMOTEAPI void himote_info_html_esc_write(char *string, int str_len TSRMLS_DC);
HIMOTEAPI void himote_print_info_htmlhead(TSRMLS_D);
HIMOTEAPI void himote_print_info(int flag TSRMLS_DC);
HIMOTEAPI void himote_print_style(void);
HIMOTEAPI void himote_info_print_style(TSRMLS_D);
HIMOTEAPI void himote_info_print_table_colspan_header(int num_cols, char *header);
HIMOTEAPI void himote_info_print_table_header(int num_cols, ...);
HIMOTEAPI void himote_info_print_table_row(int num_cols, ...);
HIMOTEAPI void himote_info_print_table_row_ex(int num_cols, const char *, ...);
HIMOTEAPI void himote_info_print_table_start(void);
HIMOTEAPI void himote_info_print_table_end(void);
HIMOTEAPI void himote_info_print_box_start(int bg);
HIMOTEAPI void himote_info_print_box_end(void);
HIMOTEAPI void himote_info_print_hr(void);
HIMOTEAPI void himote_info_print_module(zend_module_entry *module TSRMLS_DC);
HIMOTEAPI char *himote_logo_guid(void);
HIMOTEAPI char *himote_get_uname(char mode);

void register_himoteinfo_constants(INIT_FUNC_ARGS);
END_EXTERN_C()

#endif /* HIMOTE_INFO_H */
