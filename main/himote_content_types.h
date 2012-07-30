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

#ifndef HIMOTE_CONTENT_TYPES_H
#define HIMOTE_CONTENT_TYPES_H

#define DEFAULT_POST_CONTENT_TYPE "application/x-www-form-urlencoded"

SAPI_API SAPI_POST_READER_FUNC(himote_default_post_reader);
SAPI_API SAPI_POST_HANDLER_FUNC(himote_std_post_handler);
int himote_startup_sapi_content_types(TSRMLS_D);
int himote_setup_sapi_content_types(TSRMLS_D);

#endif /* HIMOTE_CONTENT_TYPES_H */
