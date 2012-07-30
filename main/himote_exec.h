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
   | Author: Rasmus Lerdorf <rasmus@lerdorf.on.ca>                        |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef EXEC_H
#define EXEC_H

HIMOTE_FUNCTION(system);
HIMOTE_FUNCTION(exec);
HIMOTE_FUNCTION(escapeshellcmd);
HIMOTE_FUNCTION(escapeshellarg);
HIMOTE_FUNCTION(passthru);
HIMOTE_FUNCTION(shell_exec);
HIMOTE_FUNCTION(proc_open);
HIMOTE_FUNCTION(proc_get_status);
HIMOTE_FUNCTION(proc_close);
HIMOTE_FUNCTION(proc_terminate);
HIMOTE_FUNCTION(proc_nice);
HIMOTE_MINIT_FUNCTION(proc_open);

HIMOTEAPI char *himote_escape_shell_cmd(char *);
HIMOTEAPI char *himote_escape_shell_arg(char *);
HIMOTEAPI int himote_exec(int type, char *cmd, zval *array, zval *return_value TSRMLS_DC);

#endif /* EXEC_H */
