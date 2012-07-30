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
   | Authors: Andi Gutmans <andi@zend.com>                                |
   |          Zeev Suraski <zeev@zend.com>                                |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#ifndef HIMOTE_MAIN_H
#define HIMOTE_MAIN_H

#include "zend_globals.h"
#include "himote_globals.h"
#include "SAPI.h"

BEGIN_EXTERN_C()
HIMOTEAPI int himote_request_startup(TSRMLS_D);
HIMOTEAPI void himote_request_shutdown(void *dummy);
HIMOTEAPI void himote_request_shutdown_for_exec(void *dummy);
HIMOTEAPI int himote_module_startup(sapi_module_struct *sf, zend_module_entry *additional_modules, uint num_additional_modules);
HIMOTEAPI void himote_module_shutdown(TSRMLS_D);
HIMOTEAPI void himote_module_shutdown_for_exec(void);
HIMOTEAPI int himote_module_shutdown_wrapper(sapi_module_struct *sapi_globals);
HIMOTEAPI int himote_request_startup_for_hook(TSRMLS_D);

HIMOTEAPI int himote_register_extensions(zend_module_entry **ptr, int count TSRMLS_DC);

HIMOTEAPI int himote_execute_script(zend_file_handle *primary_file TSRMLS_DC);
HIMOTEAPI int himote_execute_simple_script(zend_file_handle *primary_file, zval **ret TSRMLS_DC);
HIMOTEAPI int himote_handle_special_queries(TSRMLS_D);
HIMOTEAPI int himote_lint_script(zend_file_handle *file TSRMLS_DC);

HIMOTEAPI void himote_handle_aborted_connection(void);
HIMOTEAPI int himote_handle_auth_data(const char *auth TSRMLS_DC);

HIMOTEAPI void himote_html_puts(const char *str, uint siz TSRMLS_DC);
HIMOTEAPI int himote_stream_open_for_zend_ex(const char *filename, zend_file_handle *handle, int mode TSRMLS_DC);

extern void himote_call_shutdown_functions(TSRMLS_D);
extern void himote_free_shutdown_functions(TSRMLS_D);

/* environment module */
extern int himote_init_environ(void);
extern int himote_shutdown_environ(void);
END_EXTERN_C()

#endif
