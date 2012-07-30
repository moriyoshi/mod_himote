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
   | Author: Jani Lehtimäki <jkl@njet.net>                                |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_VAR_H
#define HIMOTE_VAR_H

#include "himote_smart_str_public.h"

HIMOTE_FUNCTION(var_dump);
HIMOTE_FUNCTION(var_export);
HIMOTE_FUNCTION(debug_zval_dump);
HIMOTE_FUNCTION(serialize);
HIMOTE_FUNCTION(unserialize);
HIMOTE_FUNCTION(memory_get_usage);
HIMOTE_FUNCTION(memory_get_peak_usage);

HIMOTEAPI void himote_var_dump(zval **struc, int level TSRMLS_DC);
HIMOTEAPI void himote_var_export(zval **struc, int level TSRMLS_DC);
HIMOTEAPI void himote_var_export_ex(zval **struc, int level, smart_str *buf TSRMLS_DC);

HIMOTEAPI void himote_debug_zval_dump(zval **struc, int level TSRMLS_DC);

/* typdef HashTable himote_serialize_data_t; */
#define himote_serialize_data_t HashTable

struct himote_unserialize_data {
	void *first;
	void *first_dtor;
};

typedef struct himote_unserialize_data himote_unserialize_data_t;

HIMOTEAPI void himote_var_serialize(smart_str *buf, zval **struc, himote_serialize_data_t *var_hash TSRMLS_DC);
HIMOTEAPI int himote_var_unserialize(zval **rval, const unsigned char **p, const unsigned char *max, himote_unserialize_data_t *var_hash TSRMLS_DC);

#define HIMOTE_VAR_SERIALIZE_INIT(var_hash) \
   zend_hash_init(&(var_hash), 10, NULL, NULL, 0)
#define HIMOTE_VAR_SERIALIZE_DESTROY(var_hash) \
   zend_hash_destroy(&(var_hash))

#define HIMOTE_VAR_UNSERIALIZE_INIT(var_hash) \
	(var_hash).first = 0; \
	(var_hash).first_dtor = 0
#define HIMOTE_VAR_UNSERIALIZE_DESTROY(var_hash) \
	var_destroy(&(var_hash))

HIMOTEAPI void var_replace(himote_unserialize_data_t *var_hash, zval *ozval, zval **nzval);
HIMOTEAPI void var_push_dtor(himote_unserialize_data_t *var_hash, zval **val);
HIMOTEAPI void var_destroy(himote_unserialize_data_t *var_hash);

#define HIMOTE_VAR_UNSERIALIZE_ZVAL_CHANGED(var_hash, ozval, nzval) \
	var_replace((var_hash), (ozval), &(nzval))
	
HIMOTEAPI zend_class_entry *himote_create_empty_class(char *class_name, int len);

static inline int himote_varname_check(char *name, int name_len, zend_bool silent TSRMLS_DC) /* {{{ */
{
    if (name_len == sizeof("GLOBALS") - 1 && !memcmp(name, "GLOBALS", sizeof("GLOBALS") - 1)) {
		if (!silent) {
			himote_error_docref(NULL TSRMLS_CC, E_WARNING, "Attempted GLOBALS variable overwrite");
		}
        return FAILURE;
    } else if (name[0] == '_' &&
            (
             (name_len == sizeof("_GET") - 1 && !memcmp(name, "_GET", sizeof("_GET") - 1)) ||
             (name_len == sizeof("_POST") - 1 && !memcmp(name, "_POST", sizeof("_POST") - 1)) ||
             (name_len == sizeof("_COOKIE") - 1 && !memcmp(name, "_COOKIE", sizeof("_COOKIE") - 1)) ||
             (name_len == sizeof("_ENV") - 1 && !memcmp(name, "_ENV", sizeof("_ENV") - 1)) ||
             (name_len == sizeof("_SERVER") - 1 && !memcmp(name, "_SERVER", sizeof("_SERVER") - 1)) ||
             (name_len == sizeof("_SESSION") - 1 && !memcmp(name, "_SESSION", sizeof("_SESSION") - 1)) ||
             (name_len == sizeof("_FILES") - 1  && !memcmp(name, "_FILES", sizeof("_FILES") - 1)) ||
             (name_len == sizeof("_REQUEST") -1 && !memcmp(name, "_REQUEST", sizeof("_REQUEST") - 1))
            )
            ) {
		if (!silent) {
			himote_error_docref(NULL TSRMLS_CC, E_WARNING, "Attempted super-global (%s) variable overwrite", name);
		}
        return FAILURE;
    } else if (name[0] == 'H' &&
            (
             (name_len == sizeof("HTTP_POST_VARS") - 1 && !memcmp(name, "HTTP_POST_VARS", sizeof("HTTP_POST_VARS") - 1)) ||
             (name_len == sizeof("HTTP_GET_VARS") - 1 && !memcmp(name, "HTTP_GET_VARS", sizeof("HTTP_GET_VARS") - 1)) ||
             (name_len == sizeof("HTTP_COOKIE_VARS") - 1 && !memcmp(name, "HTTP_COOKIE_VARS", sizeof("HTTP_COOKIE_VARS") - 1)) ||
             (name_len == sizeof("HTTP_ENV_VARS") - 1 && !memcmp(name, "HTTP_ENV_VARS", sizeof("HTTP_ENV_VARS") - 1)) ||
             (name_len == sizeof("HTTP_SERVER_VARS") - 1 && !memcmp(name, "HTTP_SERVER_VARS", sizeof("HTTP_SERVER_VARS") - 1)) ||
             (name_len == sizeof("HTTP_SESSION_VARS") - 1 && !memcmp(name, "HTTP_SESSION_VARS", sizeof("HTTP_SESSION_VARS") - 1)) ||
             (name_len == sizeof("HTTP_RAW_POST_DATA") - 1 && !memcmp(name, "HTTP_RAW_POST_DATA", sizeof("HTTP_RAW_POST_DATA") - 1)) ||
             (name_len == sizeof("HTTP_POST_FILES") - 1 && !memcmp(name, "HTTP_POST_FILES", sizeof("HTTP_POST_FILES") - 1))
            )
            ) {
		if (!silent) {
			himote_error_docref(NULL TSRMLS_CC, E_WARNING, "Attempted long input array (%s) overwrite", name);
		}
        return FAILURE;
    }
	return SUCCESS;
}
/* }}} */

#endif /* HIMOTE_VAR_H */
