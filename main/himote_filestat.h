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
   | Author:  Jim Winstead <jimw@php.net>                                 |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_FILESTAT_H
#define HIMOTE_FILESTAT_H

HIMOTE_RINIT_FUNCTION(filestat);
HIMOTE_RSHUTDOWN_FUNCTION(filestat);

HIMOTE_FUNCTION(realpath_cache_size);
HIMOTE_FUNCTION(realpath_cache_get);
HIMOTE_FUNCTION(clearstatcache);
HIMOTE_FUNCTION(fileatime);
HIMOTE_FUNCTION(filectime);
HIMOTE_FUNCTION(filegroup);
HIMOTE_FUNCTION(fileinode);
HIMOTE_FUNCTION(filemtime);
HIMOTE_FUNCTION(fileowner);
HIMOTE_FUNCTION(fileperms);
HIMOTE_FUNCTION(filesize);
HIMOTE_FUNCTION(filetype);
HIMOTE_FUNCTION(is_writable);
HIMOTE_FUNCTION(is_readable);
HIMOTE_FUNCTION(is_executable);
HIMOTE_FUNCTION(is_file);
HIMOTE_FUNCTION(is_dir);
HIMOTE_FUNCTION(is_link);
HIMOTE_FUNCTION(file_exists);
HIMOTE_NAMED_FUNCTION(himote_if_stat);
HIMOTE_NAMED_FUNCTION(himote_if_lstat);
HIMOTE_FUNCTION(disk_total_space);
HIMOTE_FUNCTION(disk_free_space);
HIMOTE_FUNCTION(chown);
HIMOTE_FUNCTION(chgrp);
#if HAVE_LCHOWN
HIMOTE_FUNCTION(lchown);
#endif
#if HAVE_LCHOWN
HIMOTE_FUNCTION(lchgrp);
#endif
HIMOTE_FUNCTION(chmod);
#if HAVE_UTIME
HIMOTE_FUNCTION(touch);
#endif
HIMOTE_FUNCTION(clearstatcache);

#define MAKE_LONG_ZVAL_INCREF(name, val)\
	MAKE_STD_ZVAL(name); \
	ZVAL_LONG(name, val); \
	Z_ADDREF_P(name); 

#ifdef HIMOTE_WIN32
#define S_IRUSR S_IREAD
#define S_IWUSR S_IWRITE
#define S_IXUSR S_IEXEC
#define S_IRGRP S_IREAD
#define S_IWGRP S_IWRITE
#define S_IXGRP S_IEXEC
#define S_IROTH S_IREAD
#define S_IWOTH S_IWRITE
#define S_IXOTH S_IEXEC

#undef getgid
#define getgroups(a, b) 0
#define getgid() 1
#define getuid() 1
#endif

#ifdef HIMOTE_WIN32
typedef unsigned int himote_stat_len;
#else
typedef int himote_stat_len;
#endif

HIMOTEAPI void himote_clear_stat_cache(zend_bool clear_realpath_cache, const char *filename, int filename_len TSRMLS_DC);
HIMOTEAPI void himote_stat(const char *filename, himote_stat_len filename_length, int type, zval *return_value TSRMLS_DC);

/* Switches for various filestat functions: */
#define FS_PERMS    0
#define FS_INODE    1
#define FS_SIZE     2
#define FS_OWNER    3
#define FS_GROUP    4
#define FS_ATIME    5
#define FS_MTIME    6
#define FS_CTIME    7
#define FS_TYPE     8
#define FS_IS_W     9
#define FS_IS_R    10
#define FS_IS_X    11
#define FS_IS_FILE 12
#define FS_IS_DIR  13
#define FS_IS_LINK 14
#define FS_EXISTS  15
#define FS_LSTAT   16
#define FS_STAT    17

#endif /* HIMOTE_FILESTAT_H */
