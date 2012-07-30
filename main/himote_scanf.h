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
   | Author: Clayton Collie <clcollie@mindspring.com>                     |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef  SCANF_H
#define  SCANF_H


#define SCAN_MAX_ARGS   0xFF    /* Maximum number of variable which can be      */
                                /* passed to (f|s)scanf. This is an artifical   */
                                /* upper limit to keep resources in check and   */
                                /* minimize the possibility of exploits         */

#define SCAN_SUCCESS			SUCCESS	
#define SCAN_ERROR_EOF			-1	/* indicates premature termination of scan 	*/
									/* can be caused by bad parameters or format*/
									/* string.									*/
#define SCAN_ERROR_INVALID_FORMAT		(SCAN_ERROR_EOF - 1)
#define SCAN_ERROR_VAR_PASSED_BYVAL		(SCAN_ERROR_INVALID_FORMAT - 1)
#define SCAN_ERROR_WRONG_PARAM_COUNT	(SCAN_ERROR_VAR_PASSED_BYVAL - 1)
#define SCAN_ERROR_INTERNAL             (SCAN_ERROR_WRONG_PARAM_COUNT - 1)


/*  
 * The following are here solely for the benefit of the scanf type functions
 * e.g. fscanf
 */
HIMOTEAPI int ValidateFormat(char *format, int numVars, int *totalVars);
HIMOTEAPI int himote_sscanf_internal(char *string,char *format,int argCount,zval ***args,
				int varStart, zval **return_value TSRMLS_DC);


#endif /* SCANF_H */