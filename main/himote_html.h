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
   | Author: Rasmus Lerdorf <rasmus@lerdorf.on.ca>                        |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_HTML_H
#define HIMOTE_HTML_H

#define ENT_HTML_QUOTE_NONE		0
#define ENT_HTML_QUOTE_SINGLE	1
#define ENT_HTML_QUOTE_DOUBLE	2
#define ENT_HTML_IGNORE_ERRORS	4

#define ENT_COMPAT    ENT_HTML_QUOTE_DOUBLE
#define ENT_QUOTES    (ENT_HTML_QUOTE_DOUBLE | ENT_HTML_QUOTE_SINGLE)
#define ENT_NOQUOTES  ENT_HTML_QUOTE_NONE
#define ENT_IGNORE    ENT_HTML_IGNORE_ERRORS

void register_html_constants(INIT_FUNC_ARGS);

HIMOTE_FUNCTION(htmlspecialchars);
HIMOTE_FUNCTION(htmlentities);
HIMOTE_FUNCTION(htmlspecialchars_decode);
HIMOTE_FUNCTION(html_entity_decode);
HIMOTE_FUNCTION(get_html_translation_table);

HIMOTEAPI char *himote_escape_html_entities(unsigned char *old, int oldlen, int *newlen, int all, int quote_style, char *hint_charset TSRMLS_DC);
HIMOTEAPI char *himote_escape_html_entities_ex(unsigned char *old, int oldlen, int *newlen, int all, int quote_style, char *hint_charset, zend_bool double_encode TSRMLS_DC);
HIMOTEAPI char *himote_unescape_html_entities(unsigned char *old, int oldlen, int *newlen, int all, int quote_style, char *hint_charset TSRMLS_DC);

#endif /* HIMOTE_HTML_H */
