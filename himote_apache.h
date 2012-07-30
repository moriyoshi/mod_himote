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
   | Author: Sascha Schumann <sascha@schumann.cx>                         |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#ifndef HIMOTE_APACHE_H
#define HIMOTE_APACHE_H

#include "httpd.h"
#include "http_config.h"
#include "http_core.h"

/* Declare this so we can get to it from outside the sapi_apache2.c file */
extern module AP_MODULE_DECLARE_DATA himote_module;

/* A way to specify the location of the himote.ini dir in an apache directive */
extern char *apache2_himote_ini_path_override;

/* The server_context used by HIMOTE */
typedef struct himote_struct {
	int state;
	request_rec *r;
	apr_bucket_brigade *brigade;
	/* stat structure of the current file */
#if defined(NETWARE) && defined(CLIB_STAT_PATCH)
	struct stat_libc finfo;
#else
	struct stat finfo;
#endif
	/* Whether or not we've processed HIMOTE in the output filters yet. */
	int request_processed;
	/* final content type */
	char *content_type;
} himote_struct;

void *merge_himote_config(apr_pool_t *p, void *base_conf, void *new_conf);
void *create_himote_config(apr_pool_t *p, char *dummy);
char *get_himote_config(void *conf, char *name, size_t name_len);
void apply_config(void *);
extern const command_rec himote_dir_cmds[];
void himote_ap2_register_hook(apr_pool_t *p);

#define APR_ARRAY_FOREACH_OPEN(arr, key, val) 		\
{													\
	apr_table_entry_t *elts;						\
	int i;											\
	elts = (apr_table_entry_t *) arr->elts;			\
	for (i = 0; i < arr->nelts; i++) {				\
		key = elts[i].key;							\
		val = elts[i].val;

#define APR_ARRAY_FOREACH_CLOSE() }}

typedef struct {
	long engine;
	long xbithack;
	long last_modified;
} himote_apache2_info_struct;

extern zend_module_entry apache2_module_entry;

#ifdef ZTS
extern int himote_apache2_info_id;
#define AP2(v) TSRMG(himote_apache2_info_id, himote_apache2_info_struct *, v)
#else
extern himote_apache2_info_struct himote_apache2_info;
#define AP2(v) (himote_apache2_info.v)
#endif

/* fix for gcc4 visibility patch */
#ifndef HIMOTE_WIN32
# undef AP_MODULE_DECLARE_DATA
# define AP_MODULE_DECLARE_DATA HIMOTEAPI
#endif

#endif /* HIMOTE_APACHE_H */
