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
   | Author: Andrew Sitnikov <sitnikov@infonet.ee>                        |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#include "himote.h"

#include <sys/types.h>                                                                                                        

#ifdef HAVE_SYS_IPC_H
#include <sys/ipc.h>
#endif

#if HAVE_FTOK
/* {{{ proto int ftok(string pathname, string proj)
   Convert a pathname and a project identifier to a System V IPC key */
HIMOTE_FUNCTION(ftok)
{
	char *pathname, *proj;
	int pathname_len, proj_len;
	key_t k;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &pathname, &pathname_len, &proj, &proj_len) == FAILURE) {
		return;
	}

	if (strlen(pathname) != pathname_len) {
		RETURN_FALSE;
	}

	if (pathname_len == 0){
		himote_error_docref(NULL TSRMLS_CC, E_WARNING, "Pathname is invalid");
		RETURN_LONG(-1);
	}

	if (proj_len != 1){
		himote_error_docref(NULL TSRMLS_CC, E_WARNING, "Project identifier is invalid");
		RETURN_LONG(-1);
    }

	k = ftok(pathname, proj[0]);
	if (k == -1) {
		himote_error_docref(NULL TSRMLS_CC, E_WARNING, "ftok() failed - %s", strerror(errno));
	}

	RETURN_LONG(k);
}
/* }}} */
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
