/* 
   +----------------------------------------------------------------------+
   | HIMOTE Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2012 The HIMOTE Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the HIMOTE license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the HIMOTE license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Rasmus Lerdorf <rasmus@lerdorf.on.ca>                        |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_MAIL_H
#define HIMOTE_MAIL_H

HIMOTE_FUNCTION(mail);
HIMOTE_MINFO_FUNCTION(mail);

HIMOTE_FUNCTION(ezmlm_hash);
HIMOTEAPI extern int php_mail(char *to, char *subject, char *message, char *headers, char *extra_cmd TSRMLS_DC);

#endif /* HIMOTE_MAIL_H */
