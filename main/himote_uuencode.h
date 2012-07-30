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
   | Author: Ilia Alshanetsky <ilia@php.net>                              |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_UUENCODE_H
#define HIMOTE_UUENCODE_H

HIMOTE_FUNCTION(convert_uudecode);
HIMOTE_FUNCTION(convert_uuencode);

HIMOTEAPI int php_uudecode(char *src, int src_len, char **dest);
HIMOTEAPI int php_uuencode(char *src, int src_len, char **dest);

#endif /* HIMOTE_UUENCODE_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
