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
   | Authors: Rasmus Lerdorf <rasmus@php.net>                             |
   |          Zeev Suraski <zeev@zend.com>                                |
   |          Pedro Melo <melo@ip.pt>                                     |
   |          Sterling Hughes <sterling@php.net>                          |
   |                                                                      |
   | Based on code from: Shawn Cokus <Cokus@math.washington.edu>          |
   +----------------------------------------------------------------------+
 */
/* $Id$ */

#ifndef HIMOTE_RAND_H
#define	HIMOTE_RAND_H

#include "himote.h"
#include "basic_functions.h"
#include <stdlib.h>

/* System Rand functions */
#ifndef RAND_MAX
#define RAND_MAX (1<<15)
#endif

/* In ZTS mode we rely on rand_r() so we must use RAND_MAX. */
#if !defined(ZTS) && (defined(HAVE_LRAND48) || defined(HAVE_RANDOM))
#define HIMOTE_RAND_MAX 2147483647
#else
#define HIMOTE_RAND_MAX RAND_MAX
#endif

#define RAND_RANGE(__n, __min, __max, __tmax) \
    (__n) = (__min) + (long) ((double) ( (double) (__max) - (__min) + 1.0) * ((__n) / ((__tmax) + 1.0)))

/* MT Rand */
#define HIMOTE_MT_RAND_MAX ((long) (0x7FFFFFFF)) /* (1<<31) - 1 */ 

#ifdef HIMOTE_WIN32
#define GENERATE_SEED() (((long) (time(0) * GetCurrentProcessId())) ^ ((long) (1000000.0 * himote_combined_lcg(TSRMLS_C))))
#else
#define GENERATE_SEED() (((long) (time(0) * getpid())) ^ ((long) (1000000.0 * himote_combined_lcg(TSRMLS_C))))
#endif

HIMOTEAPI void himote_srand(long seed TSRMLS_DC);
HIMOTEAPI long himote_rand(TSRMLS_D);
HIMOTEAPI void himote_mt_srand(himote_uint32 seed TSRMLS_DC);
HIMOTEAPI himote_uint32 himote_mt_rand(TSRMLS_D);

#endif	/* HIMOTE_RAND_H */
