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
   | Author: Stefan Esser <sesser@php.net>                                |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef SHA1_H
#define SHA1_H

#include "basic_functions.h"

/* SHA1 context. */
typedef struct {
	himote_uint32 state[5];		/* state (ABCD) */
	himote_uint32 count[2];		/* number of bits, modulo 2^64 (lsb first) */
	unsigned char buffer[64];	/* input buffer */
} HIMOTE_SHA1_CTX;

HIMOTEAPI void HIMOTE_SHA1Init(HIMOTE_SHA1_CTX *);
HIMOTEAPI void HIMOTE_SHA1Update(HIMOTE_SHA1_CTX *, const unsigned char *, unsigned int);
HIMOTEAPI void HIMOTE_SHA1Final(unsigned char[20], HIMOTE_SHA1_CTX *);
HIMOTEAPI void make_sha1_digest(char *sha1str, unsigned char *digest);

HIMOTE_FUNCTION(sha1);
HIMOTE_FUNCTION(sha1_file);

#endif