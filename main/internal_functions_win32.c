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

/* {{{ includes
 */
#include "himote.h"
#include "himote_main.h"
#include "zend_modules.h"
#include "zend_compile.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef ZEND_ENGINE_2
#error HEAD does not work with ZendEngine1 anymore
#endif

#include "dl.h"
#include "file.h"
#include "fsock.h"
#include "head.h"
#include "pack.h"
#include "himote_browscap.h"
#include "himote_crypt.h"
#include "himote_dir.h"
#include "himote_filestat.h"
#include "himote_mail.h"
#include "himote_ext_syslog.h"
#include "himote_standard.h"
#include "himote_lcg.h"
#include "himote_array.h"
#include "himote_assert.h"
#include "ext/reflection/himote_reflection.h"
#if HAVE_BCMATH
#include "ext/bcmath/himote_bcmath.h"
#endif
#if HAVE_CALENDAR
#include "ext/calendar/himote_calendar.h"
#endif
#if HAVE_CTYPE
#include "ext/ctype/himote_ctype.h"
#endif
#if HAVE_DATE
#include "ext/date/himote_date.h"
#endif
#if HAVE_FTP
#include "ext/ftp/himote_ftp.h"
#endif
#if HAVE_ICONV
#include "ext/iconv/himote_iconv.h"
#endif
#include "reg.h"
#if HAVE_PCRE || HAVE_BUNDLED_PCRE
#include "ext/pcre/himote_pcre.h"
#endif
#if HAVE_UODBC
#include "ext/odbc/himote_odbc.h"
#endif
#if HAVE_HIMOTE_SESSION
#include "ext/session/himote_session.h"
#endif
#if HAVE_MBSTRING
#include "ext/mbstring/mbstring.h"
#endif
#if HAVE_TOKENIZER
#include "ext/tokenizer/himote_tokenizer.h"
#endif
#if HAVE_ZLIB
#include "ext/zlib/himote_zlib.h"
#endif
#if HAVE_LIBXML
#include "ext/libxml/himote_libxml.h"
#if HAVE_DOM
#include "ext/dom/himote_dom.h"
#endif
#if HAVE_SIMPLEXML
#include "ext/simplexml/himote_simplexml.h"
#endif
#endif
#if HAVE_XML
#include "ext/xml/himote_xml.h"
#endif
#if HAVE_XML && HAVE_WDDX
#include "ext/wddx/himote_wddx.h"
#endif
#ifdef HAVE_SQLITE
#include "ext/sqlite/himote_sqlite.h"
#endif
#include "ext/com_dotnet/himote_com_dotnet.h"
#ifdef HAVE_SPL
#include "ext/spl/himote_spl.h"
#endif
#if HAVE_XML && HAVE_XMLREADER
#include "ext/xmlreader/himote_xmlreader.h"
#endif
#if HAVE_XML && HAVE_XMLWRITER
#include "ext/xmlwriter/himote_xmlwriter.h"
#endif
/* }}} */

/* {{{ himote_builtin_extensions[]
 */
static zend_module_entry *himote_builtin_extensions[] = {
	himoteext_standard_ptr
#if HAVE_BCMATH
	,himoteext_bcmath_ptr
#endif
#if HAVE_CALENDAR
	,himoteext_calendar_ptr
#endif
	,himoteext_com_dotnet_ptr
#if HAVE_CTYPE
	,himoteext_ctype_ptr
#endif
#if HAVE_DATE
	,himoteext_date_ptr
#endif
#if HAVE_FTP
	,himoteext_ftp_ptr
#endif
#if HAVE_HASH
	,himoteext_hash_ptr
#endif
#if HAVE_ICONV
	,himoteext_iconv_ptr
#endif
#if HAVE_MBSTRING
	,himoteext_mbstring_ptr
#endif
#if HAVE_UODBC
	,himoteext_odbc_ptr
#endif
#if HAVE_PCRE || HAVE_BUNDLED_PCRE
	,himoteext_pcre_ptr
#endif
	,himoteext_reflection_ptr
#if HAVE_HIMOTE_SESSION
	,himoteext_session_ptr
#endif
#if HAVE_TOKENIZER
	,himoteext_tokenizer_ptr
#endif
#if HAVE_ZLIB
	,himoteext_zlib_ptr
#endif
#if HAVE_LIBXML
	,himoteext_libxml_ptr
#if HAVE_DOM
	,himoteext_dom_ptr
#endif
#if HAVE_SIMPLEXML
	,himoteext_simplexml_ptr
#endif
#endif
#if HAVE_XML
	,himoteext_xml_ptr
#endif
#if HAVE_XML && HAVE_WDDX
	,himoteext_wddx_ptr
#endif
#if HAVE_SQLITE
	,himoteext_sqlite_ptr
#endif
#if HAVE_SPL
	,himoteext_spl_ptr
#endif
#if HAVE_XML && HAVE_XMLREADER
	,himoteext_xmlreader_ptr
#endif
#if HAVE_XML && HAVE_XMLWRITER
	,himoteext_xmlwriter_ptr
#endif
};
/* }}} */

#define EXTCOUNT (sizeof(himote_builtin_extensions)/sizeof(zend_module_entry *))
	
HIMOTEAPI int himote_register_internal_extensions(TSRMLS_D)
{
	return himote_register_extensions(himote_builtin_extensions, EXTCOUNT TSRMLS_CC);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
