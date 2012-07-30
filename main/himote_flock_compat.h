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

#ifndef FLOCK_COMPAT_H
#define FLOCK_COMPAT_H

/* himote_flock internally uses fcntl whther or not flock is available
 * This way our himote_flock even works on NFS files.
 * More info: /usr/src/linux/Documentation
 */
HIMOTEAPI int himote_flock(int fd, int operation);

#ifndef HAVE_FLOCK
#	define LOCK_SH 1
#	define LOCK_EX 2
#	define LOCK_NB 4
#	define LOCK_UN 8
HIMOTEAPI int flock(int fd, int operation);
#endif

/* Userland LOCK_* constants */
#define HIMOTE_LOCK_SH 1
#define HIMOTE_LOCK_EX 2
#define HIMOTE_LOCK_UN 3
#define HIMOTE_LOCK_NB 4

#ifdef HIMOTE_WIN32
# ifdef EWOULDBLOCK
#  undef EWOULDBLOCK
# endif
# define EWOULDBLOCK WSAEWOULDBLOCK
# define fsync _commit
# define ftruncate(a, b) chsize(a, b)
#endif /* defined(HIMOTE_WIN32) */

#if !HAVE_INET_ATON
#if HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#if HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif

#ifndef HIMOTE_WIN32
extern int inet_aton(const char *, struct in_addr *); 
#endif
#endif

#endif	/* FLOCK_COMPAT_H */
