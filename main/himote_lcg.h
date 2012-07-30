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
   | Author: Sascha Schumann <sascha@schumann.cx>                         |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_LCG_H
#define HIMOTE_LCG_H

#include "basic_functions.h"

typedef struct {
	himote_int32 s1;
	himote_int32 s2;
	int seeded;
} himote_lcg_globals;

HIMOTEAPI double himote_combined_lcg(TSRMLS_D);
HIMOTE_FUNCTION(lcg_value);

HIMOTE_MINIT_FUNCTION(lcg);

#ifdef ZTS
#define LCG(v) TSRMG(lcg_globals_id, himote_lcg_globals *, v)
#else
#define LCG(v) (lcg_globals.v)
#endif

#endif
