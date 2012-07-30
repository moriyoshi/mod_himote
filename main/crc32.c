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
   | Author: Rasmus Lerdorf <rasmus@php.net>                              |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#include "himote.h"
#include "basic_functions.h"
#include "himote_crc32.h"

/* {{{ proto string crc32(string str)
   Calculate the crc32 polynomial of a string */
HIMOTE_NAMED_FUNCTION(himote_if_crc32)
{
	char *p;
	int len, nr;
	himote_uint32 crcinit = 0;
	register himote_uint32 crc;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &p, &nr) == FAILURE) {
		return;
	}
	crc = crcinit^0xFFFFFFFF;

	for (len =+nr; nr--; ++p) {
		crc = ((crc >> 8) & 0x00FFFFFF) ^ crc32tab[(crc ^ (*p)) & 0xFF ];
	}
	RETVAL_LONG(crc^0xFFFFFFFF);
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
