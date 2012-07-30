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
   | Author: Jim Winstead <jimw@php.net>                                  |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#include "himote.h"
#include "himote_pageinfo.h"
#include "SAPI.h"

#include <stdio.h>
#include <stdlib.h>
#if HAVE_PWD_H
#ifdef HIMOTE_WIN32
#include "win32/pwd.h"
#else
#include <pwd.h>
#endif
#endif
#if HAVE_GRP_H
# ifdef HIMOTE_WIN32
#  include "win32/grp.h"
# else
#  include <grp.h>
# endif
#endif
#ifdef HIMOTE_WIN32
#undef getgid
#define getgroups(a, b) 0
#define getgid() 1
#define getuid() 1
#endif
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <sys/stat.h>
#include <sys/types.h>
#ifdef HIMOTE_WIN32
#include <process.h>
#endif

#include "basic_functions.h"

/* {{{ himote_statpage
 */
HIMOTEAPI void himote_statpage(TSRMLS_D)
{
	struct stat *pstat;

	pstat = sapi_get_stat(TSRMLS_C);

	if (BG(page_uid)==-1 || BG(page_gid)==-1) {
		if(pstat) {
			BG(page_uid)   = pstat->st_uid;
			BG(page_gid)   = pstat->st_gid;
			BG(page_inode) = pstat->st_ino;
			BG(page_mtime) = pstat->st_mtime;
		} else { /* handler for situations where there is no source file, ex. himote -r */
			BG(page_uid) = getuid();
			BG(page_gid) = getgid();
		}
	}
}
/* }}} */

/* {{{ himote_getuid
 */
long himote_getuid(void)
{
	TSRMLS_FETCH();

	himote_statpage(TSRMLS_C);
	return (BG(page_uid));
}
/* }}} */

long himote_getgid(void)
{
	TSRMLS_FETCH();

	himote_statpage(TSRMLS_C);
	return (BG(page_gid));
}

/* {{{ proto int getmyuid(void)
   Get HIMOTE script owner's UID */
HIMOTE_FUNCTION(getmyuid)
{
	long uid;
	
	uid = himote_getuid();
	if (uid < 0) {
		RETURN_FALSE;
	} else {
		RETURN_LONG(uid);
	}
}
/* }}} */

/* {{{ proto int getmygid(void)
   Get HIMOTE script owner's GID */
HIMOTE_FUNCTION(getmygid)
{
	long gid;
	
	gid = himote_getgid();
	if (gid < 0) {
		RETURN_FALSE;
	} else {
		RETURN_LONG(gid);
	}
}
/* }}} */

/* {{{ proto int getmypid(void)
   Get current process ID */
HIMOTE_FUNCTION(getmypid)
{
	int pid;
	
	pid = getpid();
	if (pid < 0) {
		RETURN_FALSE;
	} else {
		RETURN_LONG((long) pid);
	}
}
/* }}} */

/* {{{ proto int getmyinode(void)
   Get the inode of the current script being parsed */
HIMOTE_FUNCTION(getmyinode)
{
	himote_statpage(TSRMLS_C);
	if (BG(page_inode) < 0) {
		RETURN_FALSE;
	} else {
		RETURN_LONG(BG(page_inode));
	}
}
/* }}} */

HIMOTEAPI long himote_getlastmod(TSRMLS_D)
{
	himote_statpage(TSRMLS_C);
	return BG(page_mtime);
}

/* {{{ proto int getlastmod(void)
   Get time of last page modification */
HIMOTE_FUNCTION(getlastmod)
{
	long lm = himote_getlastmod(TSRMLS_C);
	if (lm < 0) {
		RETURN_FALSE;
	} else {
		RETURN_LONG(lm);
	}
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
