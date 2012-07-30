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
   | Author: Wez Furlong <wez@thebrainroom.com>                           |
   +----------------------------------------------------------------------+
 */
/* $Id$ */

#ifdef HIMOTE_WIN32
typedef HANDLE himote_file_descriptor_t;
typedef DWORD himote_process_id_t;
#else
typedef int himote_file_descriptor_t;
typedef pid_t himote_process_id_t;
#endif

#define HIMOTE_PROC_OPEN_MAX_DESCRIPTORS	16

/* Environment block under win32 is a NUL terminated sequence of NUL terminated
 * name=value strings.
 * Under unix, it is an argv style array.
 * */
typedef struct _himote_process_env {
	char *envp;
#ifndef HIMOTE_WIN32
	char **envarray;
#endif
} himote_process_env_t;

struct himote_process_handle {
	himote_process_id_t	child;
#ifdef HIMOTE_WIN32
	HANDLE childHandle;
#endif
	int npipes;
	long pipes[HIMOTE_PROC_OPEN_MAX_DESCRIPTORS];
	char *command;
	int is_persistent;
	himote_process_env_t env;
};

