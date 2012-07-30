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
   | Author: Stig Bakken <ssb@php.net>                                    |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_TICKS_H
#define HIMOTE_TICKS_H

int himote_startup_ticks(TSRMLS_D);
void himote_deactivate_ticks(TSRMLS_D);
void himote_shutdown_ticks(TSRMLS_D);
void himote_run_ticks(int count);

BEGIN_EXTERN_C()
HIMOTEAPI void himote_add_tick_function(void (*func)(int));
HIMOTEAPI void himote_remove_tick_function(void (*func)(int));
END_EXTERN_C()

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
