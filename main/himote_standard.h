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

#include "basic_functions.h"
#include "himote_math.h"
#include "himote_string.h"
#include "himote_base64.h"
#include "himote_dir.h"
#include "himote_dns.h"
#include "himote_mail.h"
#include "himote_md5.h"
#include "himote_sha1.h"
#include "himote_html.h"
#include "himote_exec.h"
#include "himote_file.h"
#include "himote_ext_syslog.h"
#include "himote_filestat.h"
#include "himote_browscap.h"
#include "himote_pack.h"
#include "himote_datetime.h"
#include "himote_microtime.h"
#include "himote_url.h"
#include "himote_pageinfo.h"
#include "himote_cyr_convert.h"
#include "himote_link.h"
#include "himote_fsock.h"
#include "himote_image.h"
#include "himote_iptc.h"
#include "himote_info.h"
#include "himote_uniqid.h"
#include "himote_var.h"
#include "himote_quot_print.h"
#include "himote_dl.h"
#include "himote_crypt.h"
#include "head.h"
#include "himote_lcg.h"
#include "himote_metaphone.h"
#include "himote_output.h"
#include "himote_array.h"
#include "himote_assert.h"
#include "himote_versioning.h"
#include "himote_ftok.h"
#include "himote_type.h"


#define himoteext_standard_ptr basic_functions_module_ptr
HIMOTE_MINIT_FUNCTION(standard_filters);
HIMOTE_MSHUTDOWN_FUNCTION(standard_filters);


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
