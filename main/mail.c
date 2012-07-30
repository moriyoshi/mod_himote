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
   | Author: Rasmus Lerdorf <rasmus@php.net>                              |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "himote.h"
#include "himote_info.h"
#include "himote_string.h"
#include "basic_functions.h"

#if HAVE_SYSEXITS_H
#include <sysexits.h>
#endif
#if HAVE_SYS_SYSEXITS_H
#include <sys/sysexits.h>
#endif

#if HIMOTE_SIGCHILD
#if HAVE_SIGNAL_H
#include <signal.h>
#endif
#endif

#include "himote_mail.h"
#include "himote_ini.h"
#include "himote_string.h"
#include "himote_exec.h"

#ifdef HIMOTE_WIN32
#include "win32/sendmail.h"
#endif

#ifdef NETWARE
#define EX_OK           0       /* successful termination */
#define EX_TEMPFAIL     75      /* temp failure; user is invited to retry */
#endif

#define SKIP_LONG_HEADER_SEP(str, pos)																	\
	if (str[pos] == '\r' && str[pos + 1] == '\n' && (str[pos + 2] == ' ' || str[pos + 2] == '\t')) {	\
		pos += 2;																						\
		while (str[pos + 1] == ' ' || str[pos + 1] == '\t') {											\
			pos++;																						\
		}																								\
		continue;																						\
	}																									\

#define MAIL_ASCIIZ_CHECK(str, len)				\
	p = str;									\
	e = p + len;								\
	while ((p = memchr(p, '\0', (e - p)))) {	\
		*p = ' ';								\
	}											\

extern long himote_getuid(void);

/* {{{ proto int ezmlm_hash(string addr)
   Calculate EZMLM list hash value. */
HIMOTE_FUNCTION(ezmlm_hash)
{
	char *str = NULL;
	unsigned int h = 5381;
	int j, str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &str_len) == FAILURE) {
		return;
	}

	for (j = 0; j < str_len; j++) {
		h = (h + (h << 5)) ^ (unsigned long) (unsigned char) tolower(str[j]);
	}

	h = (h % 53);

	RETURN_LONG((int) h);
}
/* }}} */

/* {{{ proto int mail(string to, string subject, string message [, string additional_headers [, string additional_parameters]])
   Send an email message */
HIMOTE_FUNCTION(mail)
{
	char *to=NULL, *message=NULL, *headers=NULL, *headers_trimmed=NULL;
	char *subject=NULL, *extra_cmd=NULL;
	int to_len, message_len, headers_len = 0;
	int subject_len, extra_cmd_len = 0, i;
	char *force_extra_parameters = INI_STR("mail.force_extra_parameters");
	char *to_r, *subject_r;
	char *p, *e;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sss|ss",	&to, &to_len, &subject, &subject_len, &message, &message_len,
																	&headers, &headers_len, &extra_cmd, &extra_cmd_len) == FAILURE
	) {
		return;
	}

	/* ASCIIZ check */
	MAIL_ASCIIZ_CHECK(to, to_len);
	MAIL_ASCIIZ_CHECK(subject, subject_len);
	MAIL_ASCIIZ_CHECK(message, message_len);
	if (headers) {
		MAIL_ASCIIZ_CHECK(headers, headers_len);
		headers_trimmed = himote_trim(headers, headers_len, NULL, 0, NULL, 2 TSRMLS_CC);
	}
	if (extra_cmd) {
		MAIL_ASCIIZ_CHECK(extra_cmd, extra_cmd_len);
	}

	if (to_len > 0) {
		to_r = estrndup(to, to_len);
		for (; to_len; to_len--) {
			if (!isspace((unsigned char) to_r[to_len - 1])) {
				break;
			}
			to_r[to_len - 1] = '\0';
		}
		for (i = 0; to_r[i]; i++) {
			if (iscntrl((unsigned char) to_r[i])) {
				/* According to RFC 822, section 3.1.1 long headers may be separated into
				 * parts using CRLF followed at least one linear-white-space character ('\t' or ' ').
				 * To prevent these separators from being replaced with a space, we use the
				 * SKIP_LONG_HEADER_SEP to skip over them. */
				SKIP_LONG_HEADER_SEP(to_r, i);
				to_r[i] = ' ';
			}
		}
	} else {
		to_r = to;
	}

	if (subject_len > 0) {
		subject_r = estrndup(subject, subject_len);
		for (; subject_len; subject_len--) {
			if (!isspace((unsigned char) subject_r[subject_len - 1])) {
				break;
			}
			subject_r[subject_len - 1] = '\0';
		}
		for (i = 0; subject_r[i]; i++) {
			if (iscntrl((unsigned char) subject_r[i])) {
				SKIP_LONG_HEADER_SEP(subject_r, i);
				subject_r[i] = ' ';
			}
		}
	} else {
		subject_r = subject;
	}

	if (force_extra_parameters) {
		extra_cmd = himote_escape_shell_cmd(force_extra_parameters);
	} else if (extra_cmd) {
		extra_cmd = himote_escape_shell_cmd(extra_cmd);
	}

	if (himote_mail(to_r, subject_r, message, headers_trimmed, extra_cmd TSRMLS_CC)) {
		RETVAL_TRUE;
	} else {
		RETVAL_FALSE;
	}

	if (headers_trimmed) {
		efree(headers_trimmed);
	}

	if (extra_cmd) {
		efree (extra_cmd);
	}
	if (to_r != to) {
		efree(to_r);
	}
	if (subject_r != subject) {
		efree(subject_r);
	}
}
/* }}} */

/* {{{ himote_mail
 */
HIMOTEAPI int himote_mail(char *to, char *subject, char *message, char *headers, char *extra_cmd TSRMLS_DC)
{
#if (defined HIMOTE_WIN32 || defined NETWARE)
	int tsm_err;
	char *tsm_errmsg = NULL;
#endif
	FILE *sendmail;
	int ret;
	char *sendmail_path = INI_STR("sendmail_path");
	char *sendmail_cmd = NULL;
	char *mail_log = INI_STR("mail.log");
	char *hdr = headers;
#if HIMOTE_SIGCHILD
	void (*sig_handler)() = NULL;
#endif

#define MAIL_RET(val) \
	if (hdr != headers) {	\
		efree(hdr);	\
	}	\
	return val;	\

	if (mail_log && *mail_log) {
		char *tmp;
		int l = spprintf(&tmp, 0, "mail() on [%s:%d]: To: %s -- Headers: %s\n", zend_get_executed_filename(TSRMLS_C), zend_get_executed_lineno(TSRMLS_C), to, hdr ? hdr : "");
		himote_stream *stream = himote_stream_open_wrapper(mail_log, "a", IGNORE_URL_WIN | REPORT_ERRORS | STREAM_DISABLE_OPEN_BASEDIR, NULL);

		if (hdr) { /* find all \r\n instances and replace them with spaces, so a log line is always one line long */ 
			char *p = tmp;
			while ((p = strpbrk(p, "\r\n"))) {
				*p = ' ';
			}
			tmp[l - 1] = '\n';
		}
		if (stream) {
			himote_stream_write(stream, tmp, l);
			himote_stream_close(stream);
		}
		efree(tmp);
	}
	if (PG(mail_x_header)) {
		char *tmp = zend_get_executed_filename(TSRMLS_C);
		char *f;
		size_t f_len;

		himote_basename(tmp, strlen(tmp), NULL, 0,&f, &f_len TSRMLS_CC);

		if (headers != NULL) {
			spprintf(&hdr, 0, "X-HIMOTE-Originating-Script: %ld:%s\n%s", himote_getuid(), f, headers);
		} else {
			spprintf(&hdr, 0, "X-HIMOTE-Originating-Script: %ld:%s\n", himote_getuid(), f);
		}
		efree(f);
	}

	if (!sendmail_path) {
#if (defined HIMOTE_WIN32 || defined NETWARE)
		/* handle old style win smtp sending */
		if (TSendMail(INI_STR("SMTP"), &tsm_err, &tsm_errmsg, hdr, subject, to, message, NULL, NULL, NULL TSRMLS_CC) == FAILURE) {
			if (tsm_errmsg) {
				himote_error_docref(NULL TSRMLS_CC, E_WARNING, "%s", tsm_errmsg);
				efree(tsm_errmsg);
			} else {
				himote_error_docref(NULL TSRMLS_CC, E_WARNING, "%s", GetSMErrorText(tsm_err));
			}
			MAIL_RET(0);
		}
		MAIL_RET(1);
#else
		MAIL_RET(0);
#endif
	}
	if (extra_cmd != NULL) {
		spprintf(&sendmail_cmd, 0, "%s %s", sendmail_path, extra_cmd);
	} else {
		sendmail_cmd = sendmail_path;
	}

#if HIMOTE_SIGCHILD
	/* Set signal handler of SIGCHLD to default to prevent other signal handlers
	 * from being called and reaping the return code when our child exits.
	 * The original handler needs to be restored after pclose() */
	sig_handler = (void *)signal(SIGCHLD, SIG_DFL);
	if (sig_handler == SIG_ERR) {
		sig_handler = NULL;
	}
#endif

#ifdef HIMOTE_WIN32
	sendmail = popen(sendmail_cmd, "wb");
#else
	/* Since popen() doesn't indicate if the internal fork() doesn't work
	 * (e.g. the shell can't be executed) we explicitely set it to 0 to be
	 * sure we don't catch any older errno value. */
	errno = 0;
	sendmail = popen(sendmail_cmd, "w");
#endif
	if (extra_cmd != NULL) {
		efree (sendmail_cmd);
	}

	if (sendmail) {
#ifndef HIMOTE_WIN32
		if (EACCES == errno) {
			himote_error_docref(NULL TSRMLS_CC, E_WARNING, "Permission denied: unable to execute shell to run mail delivery binary '%s'", sendmail_path);
			pclose(sendmail);
#if HIMOTE_SIGCHILD
			/* Restore handler in case of error on Windows
			   Not sure if this applicable on Win but just in case. */
			if (sig_handler) {
				signal(SIGCHLD, sig_handler);
			}
#endif
			MAIL_RET(0);
		}
#endif
		fprintf(sendmail, "To: %s\n", to);
		fprintf(sendmail, "Subject: %s\n", subject);
		if (hdr != NULL) {
			fprintf(sendmail, "%s\n", hdr);
		}
		fprintf(sendmail, "\n%s\n", message);
		ret = pclose(sendmail);

#if HIMOTE_SIGCHILD
		if (sig_handler) {
			signal(SIGCHLD, sig_handler);
		}
#endif

#ifdef HIMOTE_WIN32
		if (ret == -1)
#else
#if defined(EX_TEMPFAIL)
		if ((ret != EX_OK)&&(ret != EX_TEMPFAIL))
#elif defined(EX_OK)
		if (ret != EX_OK)
#else
		if (ret != 0)
#endif
#endif
		{
			MAIL_RET(0);
		} else {
			MAIL_RET(1);
		}
	} else {
		himote_error_docref(NULL TSRMLS_CC, E_WARNING, "Could not execute mail delivery program '%s'", sendmail_path);
#if HIMOTE_SIGCHILD
		if (sig_handler) {
			signal(SIGCHLD, sig_handler);						
		}
#endif
		MAIL_RET(0);
	}

	MAIL_RET(1); /* never reached */
}
/* }}} */

/* {{{ HIMOTE_MINFO_FUNCTION
 */
HIMOTE_MINFO_FUNCTION(mail)
{
	char *sendmail_path = INI_STR("sendmail_path");

#ifdef HIMOTE_WIN32
	if (!sendmail_path) {
		himote_info_print_table_row(2, "Internal Sendmail Support for Windows", "enabled");
	} else {
		himote_info_print_table_row(2, "Path to sendmail", sendmail_path);
	}
#else
	himote_info_print_table_row(2, "Path to sendmail", sendmail_path);
#endif
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
