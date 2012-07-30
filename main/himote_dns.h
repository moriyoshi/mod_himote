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
   | Authors: The typical suspects                                        |
   |          Marcus Boerger <helly@php.net>                              |
   |          Pollita <pollita@php.net>                                   |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_DNS_H
#define HIMOTE_DNS_H

#if defined(HAVE_DNS_SEARCH)
#define himote_dns_search(res, dname, class, type, answer, anslen) \
    	((int)dns_search(res, dname, class, type, answer, anslen, (struct sockaddr *)&from, &fromsize))
#define himote_dns_free_handle(res) \
		dns_free(res)

#elif defined(HAVE_RES_NSEARCH)
#define himote_dns_search(res, dname, class, type, answer, anslen) \
			res_nsearch(res, dname, class, type, answer, anslen);
#define himote_dns_free_handle(res) \
			res_nclose(res); \
			himote_dns_free_res(*res)

#elif defined(HAVE_RES_SEARCH)
#define himote_dns_search(res, dname, class, type, answer, anslen) \
			res_search(dname, class, type, answer, anslen)
#define himote_dns_free_handle(res) /* noop */

#endif

#if defined(HAVE_DNS_SEARCH) || defined(HAVE_RES_NSEARCH) || defined(HAVE_RES_SEARCH)
#define HAVE_DNS_SEARCH_FUNC 1
#endif

#if HAVE_DNS_SEARCH_FUNC && HAVE_DN_EXPAND && HAVE_DN_SKIPNAME
#define HAVE_FULL_DNS_FUNCS 1
#endif

HIMOTE_FUNCTION(gethostbyaddr);
HIMOTE_FUNCTION(gethostbyname);
HIMOTE_FUNCTION(gethostbynamel);

#ifdef HAVE_GETHOSTNAME
HIMOTE_FUNCTION(gethostname);
#endif

#if defined(HIMOTE_WIN32) || (HAVE_DNS_SEARCH_FUNC && !(defined(__BEOS__) || defined(NETWARE)))
HIMOTE_FUNCTION(dns_check_record);

# if defined(HIMOTE_WIN32) || HAVE_FULL_DNS_FUNCS
HIMOTE_FUNCTION(dns_get_mx);
HIMOTE_FUNCTION(dns_get_record);
HIMOTE_MINIT_FUNCTION(dns);
# endif

#endif /* defined(HIMOTE_WIN32) || (HAVE_DNS_SEARCH_FUNC && !(defined(__BEOS__) || defined(NETWARE))) */

#ifndef INT16SZ
#define INT16SZ		2
#endif

#ifndef INT32SZ
#define INT32SZ		4
#endif

#endif /* HIMOTE_DNS_H */
