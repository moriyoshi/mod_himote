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
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */


#ifndef _HIMOTE_LOGOS_H
#define _HIMOTE_LOGOS_H

BEGIN_EXTERN_C()
HIMOTEAPI int himote_register_info_logo(char *logo_string, const char *mimetype, const unsigned char *data, int size);
HIMOTEAPI int himote_unregister_info_logo(char *logo_string);
END_EXTERN_C()

int himote_init_info_logos(void);
int himote_shutdown_info_logos(void);
int himote_info_logos(const char *logo_string TSRMLS_DC);

#endif /* _HIMOTE_LOGOS_H */
