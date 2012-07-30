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

#ifndef URL_H
#define URL_H

typedef struct himote_url {
	char *scheme;
	char *user;
	char *pass;
	char *host;
	unsigned short port;
	char *path;
	char *query;
	char *fragment;
} himote_url;

HIMOTEAPI void himote_url_free(himote_url *theurl);
HIMOTEAPI himote_url *himote_url_parse(char const *str);
HIMOTEAPI himote_url *himote_url_parse_ex(char const *str, int length);
HIMOTEAPI int himote_url_decode(char *str, int len); /* return value: length of decoded string */
HIMOTEAPI int himote_raw_url_decode(char *str, int len); /* return value: length of decoded string */
HIMOTEAPI char *himote_url_encode(char const *s, int len, int *new_length);
HIMOTEAPI char *himote_raw_url_encode(char const *s, int len, int *new_length);

HIMOTE_FUNCTION(parse_url);
HIMOTE_FUNCTION(urlencode);
HIMOTE_FUNCTION(urldecode);
HIMOTE_FUNCTION(rawurlencode);
HIMOTE_FUNCTION(rawurldecode);
HIMOTE_FUNCTION(get_headers);

#define HIMOTE_URL_SCHEME 0
#define HIMOTE_URL_HOST 1
#define HIMOTE_URL_PORT 2
#define HIMOTE_URL_USER 3
#define HIMOTE_URL_PASS 4
#define HIMOTE_URL_PATH 5
#define HIMOTE_URL_QUERY 6
#define HIMOTE_URL_FRAGMENT 7

#endif /* URL_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
