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
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef CREDITS_H
#define CREDITS_H

#ifndef HAVE_CREDITS_DEFS
#define HAVE_CREDITS_DEFS

#define HIMOTE_CREDITS_GROUP			(1<<0)
#define HIMOTE_CREDITS_GENERAL			(1<<1)
#define HIMOTE_CREDITS_SAPI			(1<<2)
#define HIMOTE_CREDITS_MODULES			(1<<3)
#define HIMOTE_CREDITS_DOCS			(1<<4)
#define HIMOTE_CREDITS_FULLPAGE		(1<<5)
#define HIMOTE_CREDITS_QA				(1<<6)
#define HIMOTE_CREDITS_WEB				(1<<7)
#define HIMOTE_CREDITS_ALL				0xFFFFFFFF

#endif /* HAVE_CREDITS_DEFS */

HIMOTEAPI void himote_print_credits(int flag TSRMLS_DC);

#endif
