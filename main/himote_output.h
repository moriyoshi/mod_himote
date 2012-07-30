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

#ifndef HIMOTE_OUTPUT_H
#define HIMOTE_OUTPUT_H

typedef void (*himote_output_handler_func_t)(char *output, uint output_len, char **handled_output, uint *handled_output_len, int mode TSRMLS_DC);

BEGIN_EXTERN_C()
HIMOTEAPI void himote_output_startup(void);
HIMOTEAPI void himote_output_activate(TSRMLS_D);
HIMOTEAPI void himote_output_set_status(zend_bool status TSRMLS_DC);
HIMOTEAPI void himote_output_register_constants(TSRMLS_D);
HIMOTEAPI int  himote_default_output_func(const char *str, uint str_len TSRMLS_DC);
HIMOTEAPI int  himote_ub_body_write(const char *str, uint str_length TSRMLS_DC);
HIMOTEAPI int  himote_ub_body_write_no_header(const char *str, uint str_length TSRMLS_DC);
HIMOTEAPI int  himote_body_write(const char *str, uint str_length TSRMLS_DC);
HIMOTEAPI int  himote_header_write(const char *str, uint str_length TSRMLS_DC);
HIMOTEAPI int himote_start_ob_buffer(zval *output_handler, uint chunk_size, zend_bool erase TSRMLS_DC);
HIMOTEAPI int himote_start_ob_buffer_named(const char *output_handler_name, uint chunk_size, zend_bool erase TSRMLS_DC);
HIMOTEAPI void himote_end_ob_buffer(zend_bool send_buffer, zend_bool just_flush TSRMLS_DC);
HIMOTEAPI void himote_end_ob_buffers(zend_bool send_buffer TSRMLS_DC);
HIMOTEAPI int himote_ob_get_buffer(zval *p TSRMLS_DC);
HIMOTEAPI int himote_ob_get_length(zval *p TSRMLS_DC);
HIMOTEAPI void himote_start_implicit_flush(TSRMLS_D);
HIMOTEAPI void himote_end_implicit_flush(TSRMLS_D);
HIMOTEAPI char *himote_get_output_start_filename(TSRMLS_D);
HIMOTEAPI int himote_get_output_start_lineno(TSRMLS_D);
HIMOTEAPI void himote_ob_set_internal_handler(himote_output_handler_func_t internal_output_handler, uint buffer_size, char *handler_name, zend_bool erase TSRMLS_DC);
HIMOTEAPI int himote_ob_handler_used(char *handler_name TSRMLS_DC);
HIMOTEAPI int himote_ob_init_conflict(char *handler_new, char *handler_set TSRMLS_DC);
HIMOTEAPI int himote_ob_get_buffer(zval *p TSRMLS_DC);
HIMOTEAPI int himote_ob_get_length(zval *p TSRMLS_DC);
END_EXTERN_C()

HIMOTE_FUNCTION(ob_start);
HIMOTE_FUNCTION(ob_flush);
HIMOTE_FUNCTION(ob_clean);
HIMOTE_FUNCTION(ob_end_flush);
HIMOTE_FUNCTION(ob_end_clean);
HIMOTE_FUNCTION(ob_get_flush);
HIMOTE_FUNCTION(ob_get_clean);
HIMOTE_FUNCTION(ob_get_contents);
HIMOTE_FUNCTION(ob_get_length);
HIMOTE_FUNCTION(ob_get_level);
HIMOTE_FUNCTION(ob_get_status);
HIMOTE_FUNCTION(ob_implicit_flush);
HIMOTE_FUNCTION(ob_list_handlers);

typedef struct _himote_ob_buffer {
	char *buffer;
	uint size;
	uint text_length;
	int block_size;
	uint chunk_size;
	int status;
	zval *output_handler;
	himote_output_handler_func_t internal_output_handler;
	char *internal_output_handler_buffer;
	uint internal_output_handler_buffer_size;
	char *handler_name;
	zend_bool erase;
} himote_ob_buffer;

typedef struct _himote_output_globals {
	int (*himote_body_write)(const char *str, uint str_length TSRMLS_DC);		/* string output */
	int (*himote_header_write)(const char *str, uint str_length TSRMLS_DC);	/* unbuffer string output */
	himote_ob_buffer active_ob_buffer;
	unsigned char implicit_flush;
	char *output_start_filename;
	int output_start_lineno;
	zend_stack ob_buffers;
	int ob_nesting_level;
	zend_bool ob_lock;
	zend_bool disable_output;
} himote_output_globals;

#ifdef ZTS
#define OG(v) TSRMG(output_globals_id, himote_output_globals *, v)
ZEND_API extern int output_globals_id;
#else
#define OG(v) (output_globals.v)
ZEND_API extern himote_output_globals output_globals;
#endif

#define HIMOTE_OUTPUT_HANDLER_START		(1<<0)
#define HIMOTE_OUTPUT_HANDLER_CONT			(1<<1)
#define HIMOTE_OUTPUT_HANDLER_END			(1<<2)

#define HIMOTE_OUTPUT_HANDLER_INTERNAL     0
#define HIMOTE_OUTPUT_HANDLER_USER        1

HIMOTE_FUNCTION(output_add_rewrite_var);
HIMOTE_FUNCTION(output_reset_rewrite_vars);


#endif /* HIMOTE_OUTPUT_H */
