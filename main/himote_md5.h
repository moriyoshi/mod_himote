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
   | Author: Alexander Peslyak (Solar Designer) <solar at openwall.com>   |
   |         Rasmus Lerdorf <rasmus@lerdorf.on.ca>                        |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef MD5_H
#define MD5_H

HIMOTEAPI void make_digest(char *md5str, const unsigned char *digest);
HIMOTEAPI void make_digest_ex(char *md5str, const unsigned char *digest, int len);

HIMOTE_NAMED_FUNCTION(himote_if_md5);
HIMOTE_NAMED_FUNCTION(himote_if_md5_file);

#include "basic_functions.h"

/*
 * This is an OpenSSL-compatible implementation of the RSA Data Security,
 * Inc. MD5 Message-Digest Algorithm (RFC 1321).
 *
 * Written by Solar Designer <solar at openwall.com> in 2001, and placed
 * in the public domain.  There's absolutely no warranty.
 *
 * See md5.c for more information.
 */

/* MD5 context. */
typedef struct {
	himote_uint32 lo, hi;
	himote_uint32 a, b, c, d;
	unsigned char buffer[64];
	himote_uint32 block[16];
} HIMOTE_MD5_CTX;

HIMOTEAPI void HIMOTE_MD5Init(HIMOTE_MD5_CTX *ctx);
HIMOTEAPI void HIMOTE_MD5Update(HIMOTE_MD5_CTX *ctx, const void *data, size_t size);
HIMOTEAPI void HIMOTE_MD5Final(unsigned char *result, HIMOTE_MD5_CTX *ctx);

#endif
