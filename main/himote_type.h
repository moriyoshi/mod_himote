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

#ifndef HIMOTE_TYPE_H
#define HIMOTE_TYPE_H

HIMOTE_FUNCTION(intval);
HIMOTE_FUNCTION(floatval);
HIMOTE_FUNCTION(strval);
HIMOTE_FUNCTION(gettype);
HIMOTE_FUNCTION(settype);
HIMOTE_FUNCTION(is_null);
HIMOTE_FUNCTION(is_resource);
HIMOTE_FUNCTION(is_bool);
HIMOTE_FUNCTION(is_long);
HIMOTE_FUNCTION(is_float);
HIMOTE_FUNCTION(is_numeric);
HIMOTE_FUNCTION(is_string);
HIMOTE_FUNCTION(is_array);
HIMOTE_FUNCTION(is_object);
HIMOTE_FUNCTION(is_scalar);
HIMOTE_FUNCTION(is_callable);

#endif
