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
   | Authors: Sascha Schumann <sascha@schumann.cx>                        |
   |          Parts based on Apache 1.3 SAPI module by                    |
   |          Rasmus Lerdorf and Zeev Suraski                             |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#define ZEND_INCLUDE_FULL_WINDOWS_HEADERS

#include "himote.h"
#include "himote_ini.h"
#include "himote_apache.h"

#include "apr_strings.h"
#include "ap_config.h"
#include "util_filter.h"
#include "httpd.h"
#include "http_config.h"
#include "http_request.h"
#include "http_core.h"
#include "http_protocol.h"
#include "http_log.h"
#include "http_main.h"
#include "util_script.h"
#include "http_core.h"

#ifdef HIMOTE_AP_DEBUG
#define himoteapdebug(a) fprintf a
#else
#define himoteapdebug(a)
#endif

typedef struct {
	HashTable config;
} himote_conf_rec;

typedef struct {
	char *value;
	size_t value_len;
	char status;
	char htaccess;
} himote_dir_entry;

static const char *real_value_hnd(cmd_parms *cmd, void *dummy, const char *name, const char *value, int status)
{
	himote_conf_rec *d = dummy;
	himote_dir_entry e;

	himoteapdebug((stderr, "Getting %s=%s for %p (%d)\n", name, value, dummy, zend_hash_num_elements(&d->config)));
	
	if (!strncasecmp(value, "none", sizeof("none"))) {
		value = "";
	}
	
	e.value = apr_pstrdup(cmd->pool, value);
	e.value_len = strlen(value);
	e.status = status;
	e.htaccess = ((cmd->override & (RSRC_CONF|ACCESS_CONF)) == 0);

	zend_hash_update(&d->config, (char *) name, strlen(name) + 1, &e, sizeof(e), NULL);
	return NULL;
}

static const char *himote_apache_value_handler(cmd_parms *cmd, void *dummy, const char *name, const char *value)
{
	return real_value_hnd(cmd, dummy, name, value, HIMOTE_INI_PERDIR);
}

static const char *himote_apache_admin_value_handler(cmd_parms *cmd, void *dummy, const char *name, const char *value)
{
	return real_value_hnd(cmd, dummy, name, value, HIMOTE_INI_SYSTEM);
}

static const char *real_flag_hnd(cmd_parms *cmd, void *dummy, const char *arg1, const char *arg2, int status)
{
	char bool_val[2];

	if (!strcasecmp(arg2, "On") || (arg2[0] == '1' && arg2[1] == '\0')) {
		bool_val[0] = '1';
	} else {
		bool_val[0] = '0';
	}
	bool_val[1] = 0;

	return real_value_hnd(cmd, dummy, arg1, bool_val, status);
}

static const char *himote_apache_flag_handler(cmd_parms *cmd, void *dummy, const char *name, const char *value)
{
	return real_flag_hnd(cmd, dummy, name, value, HIMOTE_INI_PERDIR);
}

static const char *himote_apache_admin_flag_handler(cmd_parms *cmd, void *dummy, const char *name, const char *value)
{
	return real_flag_hnd(cmd, dummy, name, value, HIMOTE_INI_SYSTEM);
}

static const char *himote_apache_himoteini_set(cmd_parms *cmd, void *mconfig, const char *arg)
{
	if (apache2_himote_ini_path_override) {
		return "Only first HIMOTEINIDir directive honored per configuration tree - subsequent ones ignored";
	}
	apache2_himote_ini_path_override = ap_server_root_relative(cmd->pool, arg);
	return NULL;
}

static zend_bool should_overwrite_per_dir_entry(HashTable *target_ht, himote_dir_entry *new_per_dir_entry, zend_hash_key *hash_key, void *pData)
{
	himote_dir_entry *orig_per_dir_entry;

	if (zend_hash_find(target_ht, hash_key->arKey, hash_key->nKeyLength, (void **) &orig_per_dir_entry)==FAILURE) {
		return 1; /* does not exist in dest, copy from source */
	}

	if (new_per_dir_entry->status >= orig_per_dir_entry->status) {
		/* use new entry */
		himoteapdebug((stderr, "ADDING/OVERWRITING %s (%d vs. %d)\n", hash_key->arKey, new_per_dir_entry->status, orig_per_dir_entry->status));
		return 1;
	} else {
		return 0;
	}
}


void *merge_himote_config(apr_pool_t *p, void *base_conf, void *new_conf)
{
	himote_conf_rec *d = base_conf, *e = new_conf, *n = NULL;
#if STAS_0
	himote_dir_entry *pe;
	himote_dir_entry *data;
	char *str;
	uint str_len;
	ulong num_index;
#endif

	n = create_himote_config(p, "merge_himote_config");
	/* copy old config */
	zend_hash_copy(&n->config, &d->config, NULL, NULL, sizeof(himote_dir_entry));
	/* merge new config */
	himoteapdebug((stderr, "Merge dir (%p)+(%p)=(%p)\n", base_conf, new_conf, n));
	zend_hash_merge_ex(&n->config, &e->config, NULL, sizeof(himote_dir_entry), (merge_checker_func_t) should_overwrite_per_dir_entry, NULL);
#if STAS_0
	for (zend_hash_internal_pointer_reset(&d->config);
			zend_hash_get_current_key_ex(&d->config, &str, &str_len, 
				&num_index, 0, NULL) == HASH_KEY_IS_STRING;
			zend_hash_move_forward(&d->config)) {
		pe = NULL;
		zend_hash_get_current_data(&d->config, (void **) &data);
		if (zend_hash_find(&n->config, str, str_len, (void **) &pe) == SUCCESS) {
			if (pe->status >= data->status) continue;
		}
		himoteapdebug((stderr, "ADDING/OVERWRITING %s (%d vs. %d)\n", str, data->status, pe?pe->status:-1));
		zend_hash_update(&n->config, str, str_len, data, sizeof(*data), NULL);
	}
#endif
	return n;
}

char *get_himote_config(void *conf, char *name, size_t name_len)
{
	himote_conf_rec *d = conf;
	himote_dir_entry *pe;
	
	if (zend_hash_find(&d->config, name, name_len, (void **) &pe) == SUCCESS) {
		return pe->value;
	}

	return "";
}

void apply_config(void *dummy)
{
	himote_conf_rec *d = dummy;
	char *str;
	uint str_len;
	himote_dir_entry *data;
	
	for (zend_hash_internal_pointer_reset(&d->config);
			zend_hash_get_current_key_ex(&d->config, &str, &str_len, NULL, 0, 
				NULL) == HASH_KEY_IS_STRING;
			zend_hash_move_forward(&d->config)) {
		if (zend_hash_get_current_data(&d->config, (void **) &data) == SUCCESS) {
			himoteapdebug((stderr, "APPLYING (%s)(%s)\n", str, data->value));
			if (zend_alter_ini_entry(str, str_len, data->value, data->value_len, data->status, data->htaccess?HIMOTE_INI_STAGE_HTACCESS:HIMOTE_INI_STAGE_ACTIVATE) == FAILURE) {
				himoteapdebug((stderr, "..FAILED\n"));
			}
		}
	}
}

const command_rec himote_dir_cmds[] =
{
	AP_INIT_TAKE2("himote_value", himote_apache_value_handler, NULL, OR_OPTIONS, "HIMOTE Value Modifier"),
	AP_INIT_TAKE2("himote_flag", himote_apache_flag_handler, NULL, OR_OPTIONS, "HIMOTE Flag Modifier"),
	AP_INIT_TAKE2("himote_admin_value", himote_apache_admin_value_handler, NULL, ACCESS_CONF|RSRC_CONF, "HIMOTE Value Modifier (Admin)"),
	AP_INIT_TAKE2("himote_admin_flag", himote_apache_admin_flag_handler, NULL, ACCESS_CONF|RSRC_CONF, "HIMOTE Flag Modifier (Admin)"),
	AP_INIT_TAKE1("HIMOTEINIDir", himote_apache_himoteini_set, NULL, RSRC_CONF, "Directory containing the himote.ini file"),
	{NULL}
};

static apr_status_t destroy_himote_config(void *data)
{
	himote_conf_rec *d = data;

	himoteapdebug((stderr, "Destroying config %p\n", data));	
	zend_hash_destroy(&d->config);

	return APR_SUCCESS;
}

void *create_himote_config(apr_pool_t *p, char *dummy)
{
	himote_conf_rec *newx = (himote_conf_rec *) apr_pcalloc(p, sizeof(*newx));

	himoteapdebug((stderr, "Creating new config (%p) for %s\n", newx, dummy));
	zend_hash_init(&newx->config, 0, NULL, NULL, 1);
	apr_pool_cleanup_register(p, newx, destroy_himote_config, apr_pool_cleanup_null);
	return (void *) newx;
}

AP_MODULE_DECLARE_DATA module himote_module = {
	STANDARD20_MODULE_STUFF,
	create_himote_config,		/* create per-directory config structure */
	merge_himote_config,		/* merge per-directory config structures */
	NULL,					/* create per-server config structure */
	NULL,					/* merge per-server config structures */
	himote_dir_cmds,			/* command apr_table_t */
	himote_ap2_register_hook	/* register hooks */
};

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
