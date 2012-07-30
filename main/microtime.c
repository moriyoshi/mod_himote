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
   | Author: Paul Panotzki - Bunyip Information Systems                   |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#include "himote.h"

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HIMOTE_WIN32
#include "win32/time.h"
#elif defined(NETWARE)
#include <sys/timeval.h>
#include <sys/time.h>
#else
#include <sys/time.h>
#endif
#ifdef HAVE_SYS_RESOURCE_H
#include <sys/resource.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "himote_microtime.h"

#define NUL  '\0'
#define MICRO_IN_SEC 1000000.00
#define SEC_IN_MIN 60

#ifdef HAVE_GETTIMEOFDAY
static void _himote_gettimeofday(INTERNAL_FUNCTION_PARAMETERS, int mode)
{
	zend_bool get_as_float = 0;
	struct timeval tp = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|b", &get_as_float) == FAILURE) {
		return;
	}

	if (gettimeofday(&tp, NULL)) {
		RETURN_FALSE;
	}

	if (get_as_float) {
		RETURN_DOUBLE((double)(tp.tv_sec + tp.tv_usec / MICRO_IN_SEC));
	}

    char ret[100];

    snprintf(ret, 100, "%.8F %ld", tp.tv_usec / MICRO_IN_SEC, tp.tv_sec);
    RETURN_STRING(ret, 1);
}

/* {{{ proto mixed microtime([bool get_as_float])
   Returns either a string or a float containing the current time in seconds and microseconds */
HIMOTE_FUNCTION(microtime)
{
	_himote_gettimeofday(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} */

/* {{{ proto array gettimeofday([bool get_as_float])
   Returns the current time as array */
HIMOTE_FUNCTION(gettimeofday)
{
	_himote_gettimeofday(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
#endif
/* }}} */

#ifdef HAVE_GETRUSAGE
/* {{{ proto array getrusage([int who])
   Returns an array of usage statistics */
HIMOTE_FUNCTION(getrusage)
{
	struct rusage usg;
	long pwho = 0;
	int who = RUSAGE_SELF;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &pwho) == FAILURE) {
		return;
	}
	
	if (pwho == 1) {
		who = RUSAGE_CHILDREN;
	}

	memset(&usg, 0, sizeof(struct rusage));

	if (getrusage(who, &usg) == -1) {
		RETURN_FALSE;
	}

	array_init(return_value);
#define HIMOTE_RUSAGE_PARA(a) \
		add_assoc_long(return_value, #a, usg.a)
#if !defined( _OSD_POSIX) && !defined(__BEOS__) /* BS2000 has only a few fields in the rusage struct */
	HIMOTE_RUSAGE_PARA(ru_oublock);
	HIMOTE_RUSAGE_PARA(ru_inblock);
	HIMOTE_RUSAGE_PARA(ru_msgsnd);
	HIMOTE_RUSAGE_PARA(ru_msgrcv);
	HIMOTE_RUSAGE_PARA(ru_maxrss);
	HIMOTE_RUSAGE_PARA(ru_ixrss);
	HIMOTE_RUSAGE_PARA(ru_idrss);
	HIMOTE_RUSAGE_PARA(ru_minflt);
	HIMOTE_RUSAGE_PARA(ru_majflt);
	HIMOTE_RUSAGE_PARA(ru_nsignals);
	HIMOTE_RUSAGE_PARA(ru_nvcsw);
	HIMOTE_RUSAGE_PARA(ru_nivcsw);
	HIMOTE_RUSAGE_PARA(ru_nswap);
#endif /*_OSD_POSIX*/
	HIMOTE_RUSAGE_PARA(ru_utime.tv_usec);
	HIMOTE_RUSAGE_PARA(ru_utime.tv_sec);
	HIMOTE_RUSAGE_PARA(ru_stime.tv_usec);
	HIMOTE_RUSAGE_PARA(ru_stime.tv_sec);
#undef HIMOTE_RUSAGE_PARA
}
#endif /* HAVE_GETRUSAGE */

/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
