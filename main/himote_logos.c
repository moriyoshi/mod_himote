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
   | Author: Hartmut Holzgraefe <hholzgra@php.net>                        |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#include "himote.h"
#include "logos.h"
#include "himote_logos.h"
#include "himote_info.h"
#include "SAPI.h"

typedef struct _himote_info_logo { 
	const char *mimetype;
	int mimelen;
	const unsigned char *data; 
	int size; 
} himote_info_logo;

static HashTable himoteinfo_logo_hash;

HIMOTEAPI int himote_register_info_logo(char *logo_string, const char *mimetype, const unsigned char *data, int size)
{
	himote_info_logo info_logo;

	info_logo.mimetype = mimetype;
	info_logo.mimelen  = strlen(mimetype);
	info_logo.data     = data;
	info_logo.size     = size;

	return zend_hash_add(&himoteinfo_logo_hash, logo_string, strlen(logo_string), &info_logo, sizeof(himote_info_logo), NULL);
}

HIMOTEAPI int himote_unregister_info_logo(char *logo_string)
{
	return zend_hash_del(&himoteinfo_logo_hash, logo_string, strlen(logo_string));
}

int himote_init_info_logos(void)
{
	if(zend_hash_init(&himoteinfo_logo_hash, 0, NULL, NULL, 1)==FAILURE) 
		return FAILURE;

	himote_register_info_logo(HIMOTE_LOGO_GUID    , "image/gif", himote_logo    , sizeof(himote_logo));
	himote_register_info_logo(HIMOTE_EGG_LOGO_GUID, "image/gif", himote_egg_logo, sizeof(himote_egg_logo));
	himote_register_info_logo(ZEND_LOGO_GUID   , "image/gif", zend_logo   , sizeof(zend_logo));

	return SUCCESS;
}

int himote_shutdown_info_logos(void)
{
	zend_hash_destroy(&himoteinfo_logo_hash);
	return SUCCESS;
}

#define CONTENT_TYPE_HEADER "Content-Type: "
int himote_info_logos(const char *logo_string TSRMLS_DC)
{
	himote_info_logo *logo_image;
	char *content_header;
	int len;

	if(FAILURE==zend_hash_find(&himoteinfo_logo_hash, (char *) logo_string, strlen(logo_string), (void **)&logo_image))
		return 0;

	len = sizeof(CONTENT_TYPE_HEADER) - 1 + logo_image->mimelen;
	content_header = emalloc(len + 1);
	memcpy(content_header, CONTENT_TYPE_HEADER, sizeof(CONTENT_TYPE_HEADER) - 1);
	memcpy(content_header + sizeof(CONTENT_TYPE_HEADER) - 1 , logo_image->mimetype, logo_image->mimelen);
	content_header[len] = '\0';
	sapi_add_header(content_header, len, 0);

	HIMOTEWRITE(logo_image->data, logo_image->size);
	return 1;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
