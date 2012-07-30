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
   | Author:  Sascha Schumann <sascha@schumann.cx>                        |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_INCOMPLETE_CLASS_H
#define HIMOTE_INCOMPLETE_CLASS_H

#include "basic_functions.h"

#define HIMOTE_IC_ENTRY \
	BG(incomplete_class)

#define HIMOTE_SET_CLASS_ATTRIBUTES(struc) \
	/* OBJECTS_FIXME: Fix for new object model */	\
	if (Z_OBJ_HT_P(struc)->get_class_entry && \
            Z_OBJCE_P(struc) == BG(incomplete_class)) {	\
		class_name = himote_lookup_class_name(struc, &name_len); \
		if (!class_name) { \
			name_len = sizeof(INCOMPLETE_CLASS) - 1; \
			class_name = estrndup(INCOMPLETE_CLASS, name_len); \
		} \
		free_class_name = 1; \
		incomplete_class = 1; \
	} else { \
		free_class_name = !zend_get_object_classname(struc, &class_name, &name_len TSRMLS_CC);\
	}

#define HIMOTE_CLEANUP_CLASS_ATTRIBUTES()	\
	if (free_class_name) efree(class_name)

#define HIMOTE_CLASS_ATTRIBUTES											\
	char *class_name;													\
	zend_uint name_len;													\
	zend_bool free_class_name = 0;										\
	zend_bool incomplete_class = 0

#define INCOMPLETE_CLASS "__HIMOTE_Incomplete_Class"
#define MAGIC_MEMBER "__HIMOTE_Incomplete_Class_Name"

#ifdef __cplusplus
extern "C" {
#endif

HIMOTEAPI zend_class_entry *himote_create_incomplete_class(TSRMLS_D);
HIMOTEAPI char *himote_lookup_class_name(zval *object, zend_uint *nlen);
HIMOTEAPI void  himote_store_class_name(zval *object, const char *name, zend_uint len);

#ifdef __cplusplus
};
#endif

#endif
