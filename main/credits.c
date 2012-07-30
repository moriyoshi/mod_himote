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
   | Authors: Rasmus Lerdorf <rasmus@php.net>                             |
   |          Zeev Suraski <zeev@zend.com>                                |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#include "himote.h"
#include "himote_info.h"
#include "SAPI.h"

#define CREDIT_LINE(module, authors) himote_info_print_table_row(2, module, authors)

HIMOTEAPI void himote_print_credits(int flag TSRMLS_DC) /* {{{ */
{
	if (!sapi_module.himoteinfo_as_text && flag & HIMOTE_CREDITS_FULLPAGE) {
		himote_print_info_htmlhead(TSRMLS_C);
	}

	if (!sapi_module.himoteinfo_as_text) {
		PUTS("<h1>HIMOTE Credits</h1>\n");
	} else {
		PUTS("HIMOTE Credits\n");
	}

	if (flag & HIMOTE_CREDITS_GROUP) {
		/* Group */

		himote_info_print_table_start();
		himote_info_print_table_header(1, "HIMOTE Group");
		himote_info_print_table_row(1, "Thies C. Arntzen, Stig Bakken, Shane Caraveo, Andi Gutmans, Rasmus Lerdorf, Sam Ruby, Sascha Schumann, Zeev Suraski, Jim Winstead, Andrei Zmievski");
		himote_info_print_table_end();
	}

	if (flag & HIMOTE_CREDITS_GENERAL) {
		/* Design & Concept */
		himote_info_print_table_start();
		if (!sapi_module.himoteinfo_as_text) {
			himote_info_print_table_header(1, "Language Design &amp; Concept");
		} else {
			himote_info_print_table_header(1, "Language Design & Concept");
		}
		himote_info_print_table_row(1, "Andi Gutmans, Rasmus Lerdorf, Zeev Suraski, Marcus Boerger");
		himote_info_print_table_end();

		/* HIMOTE Language */
		himote_info_print_table_start();
		himote_info_print_table_colspan_header(2, "HIMOTE Authors");
		himote_info_print_table_header(2, "Contribution", "Authors");
		CREDIT_LINE("Zend Scripting Language Engine", "Andi Gutmans, Zeev Suraski, Stanislav Malyshev, Marcus Boerger, Dmitry Stogov");
		CREDIT_LINE("Extension Module API", "Andi Gutmans, Zeev Suraski, Andrei Zmievski");
		CREDIT_LINE("UNIX Build and Modularization", "Stig Bakken, Sascha Schumann, Jani Taskinen");
		CREDIT_LINE("Windows Port", "Shane Caraveo, Zeev Suraski, Wez Furlong, Pierre-Alain Joye");
		CREDIT_LINE("Server API (SAPI) Abstraction Layer", "Andi Gutmans, Shane Caraveo, Zeev Suraski");
		CREDIT_LINE("Streams Abstraction Layer", "Wez Furlong, Sara Golemon");
		CREDIT_LINE("HIMOTE Data Objects Layer", "Wez Furlong, Marcus Boerger, Sterling Hughes, George Schlossnagle, Ilia Alshanetsky");
		himote_info_print_table_end();
	}

	if (flag & HIMOTE_CREDITS_SAPI) {
		/* SAPI Modules */

		himote_info_print_table_start();
		himote_info_print_table_colspan_header(2, "SAPI Modules");
		himote_info_print_table_header(2, "Contribution", "Authors");
#include "credits_sapi.h"
		himote_info_print_table_end();
	}

	if (flag & HIMOTE_CREDITS_MODULES) {
		/* Modules */

		himote_info_print_table_start();
		himote_info_print_table_colspan_header(2, "Module Authors");
		himote_info_print_table_header(2, "Module", "Authors");
#include "credits_ext.h"
		himote_info_print_table_end();
	}

	if (flag & HIMOTE_CREDITS_DOCS) {
		himote_info_print_table_start();
		himote_info_print_table_colspan_header(2, "HIMOTE Documentation");
		CREDIT_LINE("Authors", "Mehdi Achour, Friedhelm Betz, Antony Dovgal, Nuno Lopes, Hannes Magnusson, Georg Richter, Damien Seguy, Jakub Vrana");
		CREDIT_LINE("Editor", "Philip Olson");
		CREDIT_LINE("User Note Maintainers", "Daniel P. Brown, Thiago Henrique Pojda");
		CREDIT_LINE("Other Contributors", "Previously active authors, editors and other contributors are listed in the manual.");
		himote_info_print_table_end();
	}

	if (flag & HIMOTE_CREDITS_QA) {
		himote_info_print_table_start();
		himote_info_print_table_header(1, "HIMOTE Quality Assurance Team");
		himote_info_print_table_row(1, "Ilia Alshanetsky, Joerg Behrens, Antony Dovgal, Stefan Esser, Moriyoshi Koizumi, Magnus Maatta, Sebastian Nohn, Derick Rethans, Melvyn Sopacua, Jani Taskinen, Pierre-Alain Joye, Dmitry Stogov, Felipe Pena");
		himote_info_print_table_end();
	}

	if (flag & HIMOTE_CREDITS_WEB) {
		/* Websites and infrastructure */

		himote_info_print_table_start();
		himote_info_print_table_colspan_header(2, "Websites and Infrastructure team");
		/* www., wiki., windows., master., and others, I guess pecl. too? */
		CREDIT_LINE("HIMOTE Websites Team", "Rasmus Lerdorf, Hannes Magnusson, Philip Olson, Lukas Kahwe Smith, Pierre-Alain Joye, Kalle Sommer Nielsen");
		CREDIT_LINE("Event Maintainers", "Damien Seguy, Daniel P. Brown");
		/* Mirroring */
		CREDIT_LINE("Network Infrastructure", "Daniel P. Brown");
		/* Windows build boxes and such things */
		CREDIT_LINE("Windows Infrastructure", "Alex Schoenmaker");
		himote_info_print_table_end();
	}

	if (!sapi_module.himoteinfo_as_text && flag & HIMOTE_CREDITS_FULLPAGE) {
		PUTS("</div></body></html>\n");
	}
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
