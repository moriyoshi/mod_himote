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

#ifndef BASIC_FUNCTIONS_H
#define BASIC_FUNCTIONS_H

#include <sys/stat.h>

#ifdef HAVE_WCHAR_H
#include <wchar.h>
#endif

#include "himote_filestat.h"

#include "zend_highlight.h"

#include "url_scanner_ex.h"

extern zend_module_entry basic_functions_module;
#define basic_functions_module_ptr &basic_functions_module

HIMOTE_MINIT_FUNCTION(basic);
HIMOTE_MSHUTDOWN_FUNCTION(basic);
HIMOTE_RINIT_FUNCTION(basic);
HIMOTE_RSHUTDOWN_FUNCTION(basic);
HIMOTE_MINFO_FUNCTION(basic);

HIMOTE_FUNCTION(constant);
HIMOTE_FUNCTION(sleep);
HIMOTE_FUNCTION(usleep);
#if HAVE_NANOSLEEP
HIMOTE_FUNCTION(time_nanosleep);
HIMOTE_FUNCTION(time_sleep_until);
#endif
HIMOTE_FUNCTION(flush);
#ifdef HAVE_INET_NTOP
HIMOTE_NAMED_FUNCTION(himote_inet_ntop);
#endif
#ifdef HAVE_INET_PTON
HIMOTE_NAMED_FUNCTION(himote_inet_pton);
#endif
HIMOTE_FUNCTION(ip2long);
HIMOTE_FUNCTION(long2ip);

/* system functions */
HIMOTE_FUNCTION(getenv);
HIMOTE_FUNCTION(putenv);

HIMOTE_FUNCTION(getopt);

HIMOTE_FUNCTION(get_current_user);
HIMOTE_FUNCTION(set_time_limit);

HIMOTE_FUNCTION(get_cfg_var);
HIMOTE_FUNCTION(set_magic_quotes_runtime);
HIMOTE_FUNCTION(get_magic_quotes_runtime);
HIMOTE_FUNCTION(get_magic_quotes_gpc);

HIMOTE_FUNCTION(import_request_variables);

HIMOTE_FUNCTION(error_log);
HIMOTE_FUNCTION(error_get_last);

HIMOTE_FUNCTION(call_user_func);
HIMOTE_FUNCTION(call_user_func_array);
HIMOTE_FUNCTION(call_user_method);
HIMOTE_FUNCTION(call_user_method_array);
HIMOTE_FUNCTION(forward_static_call);
HIMOTE_FUNCTION(forward_static_call_array);

HIMOTE_FUNCTION(register_shutdown_function);
HIMOTE_FUNCTION(highlight_file);
HIMOTE_FUNCTION(highlight_string);
HIMOTE_FUNCTION(himote_strip_whitespace);
ZEND_API void himote_get_highlight_struct(zend_syntax_highlighter_ini *syntax_highlighter_ini);

HIMOTE_FUNCTION(ini_get);
HIMOTE_FUNCTION(ini_get_all);
HIMOTE_FUNCTION(ini_set);
HIMOTE_FUNCTION(ini_restore);
HIMOTE_FUNCTION(get_include_path);
HIMOTE_FUNCTION(set_include_path);
HIMOTE_FUNCTION(restore_include_path);

HIMOTE_FUNCTION(print_r);
HIMOTE_FUNCTION(fprintf);
HIMOTE_FUNCTION(vfprintf);

HIMOTE_FUNCTION(connection_aborted);
HIMOTE_FUNCTION(connection_status);
HIMOTE_FUNCTION(ignore_user_abort);

HIMOTE_FUNCTION(getservbyname);
HIMOTE_FUNCTION(getservbyport);
HIMOTE_FUNCTION(getprotobyname);
HIMOTE_FUNCTION(getprotobynumber);

HIMOTE_NAMED_FUNCTION(himote_if_crc32);

HIMOTE_FUNCTION(register_tick_function);
HIMOTE_FUNCTION(unregister_tick_function);
#ifdef HAVE_GETLOADAVG
HIMOTE_FUNCTION(sys_getloadavg);
#endif

HIMOTE_FUNCTION(is_uploaded_file);
HIMOTE_FUNCTION(move_uploaded_file);

/* From the INI parser */
HIMOTE_FUNCTION(parse_ini_file);
HIMOTE_FUNCTION(parse_ini_string);
#if ZEND_DEBUG
HIMOTE_FUNCTION(config_get_hash);
#endif

HIMOTE_FUNCTION(str_rot13);
HIMOTE_FUNCTION(stream_get_filters);
HIMOTE_FUNCTION(stream_filter_register);
HIMOTE_FUNCTION(stream_bucket_make_writeable);
HIMOTE_FUNCTION(stream_bucket_prepend);
HIMOTE_FUNCTION(stream_bucket_append);
HIMOTE_FUNCTION(stream_bucket_new);
HIMOTE_MINIT_FUNCTION(user_filters);
HIMOTE_RSHUTDOWN_FUNCTION(user_filters);
HIMOTE_RSHUTDOWN_FUNCTION(browscap);

/* Left for BC (not binary safe!) */
HIMOTEAPI int _himote_error_log(int opt_err, char *message, char *opt, char *headers TSRMLS_DC);
HIMOTEAPI int _himote_error_log_ex(int opt_err, char *message, int message_len, char *opt, char *headers TSRMLS_DC);
HIMOTEAPI int himote_prefix_varname(zval *result, zval *prefix, char *var_name, int var_name_len, zend_bool add_underscore TSRMLS_DC);

#if SIZEOF_INT == 4
/* Most 32-bit and 64-bit systems have 32-bit ints */
typedef unsigned int himote_uint32;
typedef signed int himote_int32;
#elif SIZEOF_LONG == 4
/* 16-bit systems? */
typedef unsigned long himote_uint32;
typedef signed long himote_int32;
#else
#error Need type which holds 32 bits
#endif

#define MT_N (624)

typedef struct _himote_basic_globals {
	HashTable *user_shutdown_function_names;
	HashTable putenv_ht;
	zval *strtok_zval;
	char *strtok_string;
	char *locale_string;
	char *strtok_last;
	char strtok_table[256];
	ulong strtok_len;
	char str_ebuf[40];
	zend_fcall_info array_walk_fci;
	zend_fcall_info_cache array_walk_fci_cache;
	zend_fcall_info user_compare_fci;
	zend_fcall_info_cache user_compare_fci_cache;
	zend_llist *user_tick_functions;

	zval *active_ini_file_section;

	HashTable sm_protected_env_vars;
	char *sm_allowed_env_vars;
	
	/* pageinfo.c */
	long page_uid;
	long page_gid;
	long page_inode;
	time_t page_mtime;

	/* filestat.c && main/streams/streams.c */
	char *CurrentStatFile, *CurrentLStatFile;
	himote_stream_statbuf ssb, lssb;

	/* rand.c */
	himote_uint32   state[MT_N+1];  /* state vector + 1 extra to not violate ANSI C */
	himote_uint32   *next;       /* next random value is computed from here */
	int      left;        /* can *next++ this many times before reloading */

	unsigned int rand_seed; /* Seed for rand(), in ts version */

	zend_bool rand_is_seeded; /* Whether rand() has been seeded */
	zend_bool mt_rand_is_seeded; /* Whether mt_rand() has been seeded */
    
	/* syslog.c */
	int syslog_started;
	char *syslog_device;

	/* var.c */
	zend_class_entry *incomplete_class;

	/* url_scanner_ex.re */
	url_adapt_state_ex_t url_adapt_state_ex;

#ifdef HAVE_MMAP
	void *mmap_file;
	size_t mmap_len;
#endif

	HashTable *user_filter_map;

	/* file.c */
#if defined(_REENTRANT) && defined(HAVE_MBRLEN) && defined(HAVE_MBSTATE_T)
	mbstate_t mblen_state;
#endif

	int umask;
} himote_basic_globals;

#ifdef ZTS
#define BG(v) TSRMG(basic_globals_id, himote_basic_globals *, v)
HIMOTEAPI extern int basic_globals_id;
#else
#define BG(v) (basic_globals.v)
HIMOTEAPI extern himote_basic_globals basic_globals;
#endif

#if HAVE_PUTENV
typedef struct {
	char *putenv_string;
	char *previous_value;
	char *key;
	int key_len;
} putenv_entry;
#endif

/* Values are comma-delimited
 */
#define SAFE_MODE_PROTECTED_ENV_VARS	"LD_LIBRARY_PATH"
#define SAFE_MODE_ALLOWED_ENV_VARS		"HIMOTE_"

HIMOTEAPI double himote_get_nan(void);
HIMOTEAPI double himote_get_inf(void);

#endif /* BASIC_FUNCTIONS_H */
