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
   |          Stig Sæther Bakken <ssb@php.net>                            |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

/* Synced with himote 3.0 revision 1.43 1999-06-16 [ssb] */

#ifndef HIMOTE_STRING_H
#define HIMOTE_STRING_H

HIMOTE_FUNCTION(strspn);
HIMOTE_FUNCTION(strcspn);
HIMOTE_FUNCTION(str_replace);
HIMOTE_FUNCTION(str_ireplace);
HIMOTE_FUNCTION(rtrim);
HIMOTE_FUNCTION(trim);
HIMOTE_FUNCTION(ltrim);
HIMOTE_FUNCTION(soundex);
HIMOTE_FUNCTION(levenshtein);

HIMOTE_FUNCTION(count_chars);
HIMOTE_FUNCTION(wordwrap);
HIMOTE_FUNCTION(explode);
HIMOTE_FUNCTION(implode);
HIMOTE_FUNCTION(strtok);
HIMOTE_FUNCTION(strtoupper);
HIMOTE_FUNCTION(strtolower);
HIMOTE_FUNCTION(basename);
HIMOTE_FUNCTION(dirname);
HIMOTE_FUNCTION(pathinfo);
HIMOTE_FUNCTION(strstr);
HIMOTE_FUNCTION(strpos);
HIMOTE_FUNCTION(stripos);
HIMOTE_FUNCTION(strrpos);
HIMOTE_FUNCTION(strripos);
HIMOTE_FUNCTION(strrchr);
HIMOTE_FUNCTION(substr);
HIMOTE_FUNCTION(quotemeta);
HIMOTE_FUNCTION(ucfirst);
HIMOTE_FUNCTION(lcfirst);
HIMOTE_FUNCTION(ucwords);
HIMOTE_FUNCTION(strtr);
HIMOTE_FUNCTION(strrev);
HIMOTE_FUNCTION(hebrev);
HIMOTE_FUNCTION(hebrevc);
HIMOTE_FUNCTION(user_sprintf);
HIMOTE_FUNCTION(user_printf);
HIMOTE_FUNCTION(vprintf);
HIMOTE_FUNCTION(vsprintf);
HIMOTE_FUNCTION(addcslashes);
HIMOTE_FUNCTION(addslashes);
HIMOTE_FUNCTION(stripcslashes);
HIMOTE_FUNCTION(stripslashes);
HIMOTE_FUNCTION(chr);
HIMOTE_FUNCTION(ord);
HIMOTE_FUNCTION(nl2br);
HIMOTE_FUNCTION(setlocale);
HIMOTE_FUNCTION(localeconv);
HIMOTE_FUNCTION(nl_langinfo);
HIMOTE_FUNCTION(stristr);
HIMOTE_FUNCTION(chunk_split);
HIMOTE_FUNCTION(parse_str);
HIMOTE_FUNCTION(str_getcsv);
HIMOTE_FUNCTION(bin2hex);
HIMOTE_FUNCTION(similar_text);
HIMOTE_FUNCTION(strip_tags);
HIMOTE_FUNCTION(str_repeat);
HIMOTE_FUNCTION(substr_replace);
HIMOTE_FUNCTION(strnatcmp);
HIMOTE_FUNCTION(strnatcasecmp);
HIMOTE_FUNCTION(substr_count);
HIMOTE_FUNCTION(str_pad);
HIMOTE_FUNCTION(sscanf);
HIMOTE_FUNCTION(str_shuffle);
HIMOTE_FUNCTION(str_word_count);
HIMOTE_FUNCTION(str_split);
HIMOTE_FUNCTION(strpbrk);
HIMOTE_FUNCTION(substr_compare);
#ifdef HAVE_STRCOLL
HIMOTE_FUNCTION(strcoll);
#endif
#if HAVE_STRFMON
HIMOTE_FUNCTION(money_format);
#endif

#if defined(HAVE_LOCALECONV) && defined(ZTS)
HIMOTE_MINIT_FUNCTION(localeconv);
HIMOTE_MSHUTDOWN_FUNCTION(localeconv);
#endif
#if HAVE_NL_LANGINFO
HIMOTE_MINIT_FUNCTION(nl_langinfo);
#endif

#define strnatcmp(a, b) \
	strnatcmp_ex(a, strlen(a), b, strlen(b), 0)
#define strnatcasecmp(a, b) \
	strnatcmp_ex(a, strlen(a), b, strlen(b), 1)
HIMOTEAPI int strnatcmp_ex(char const *a, size_t a_len, char const *b, size_t b_len, int fold_case);

#ifdef HAVE_LOCALECONV
HIMOTEAPI struct lconv *localeconv_r(struct lconv *out);
#endif

HIMOTEAPI char *himote_strtoupper(char *s, size_t len);
HIMOTEAPI char *himote_strtolower(char *s, size_t len);
HIMOTEAPI char *himote_strtr(char *str, int len, char *str_from, char *str_to, int trlen);
HIMOTEAPI char *himote_addslashes(char *str, int length, int *new_length, int freeit TSRMLS_DC);
HIMOTEAPI char *himote_addslashes_ex(char *str, int length, int *new_length, int freeit, int ignore_sybase TSRMLS_DC);
HIMOTEAPI char *himote_addcslashes(char *str, int length, int *new_length, int freeit, char *what, int wlength TSRMLS_DC);
HIMOTEAPI void himote_stripslashes(char *str, int *len TSRMLS_DC);
HIMOTEAPI void himote_stripcslashes(char *str, int *len);
HIMOTEAPI void himote_basename(char *s, size_t len, char *suffix, size_t sufflen, char **p_ret, size_t *p_len TSRMLS_DC);
HIMOTEAPI size_t himote_dirname(char *str, size_t len);
HIMOTEAPI char *himote_stristr(char *s, char *t, size_t s_len, size_t t_len);
HIMOTEAPI char *himote_str_to_str_ex(char *haystack, int length, char *needle,
		int needle_len, char *str, int str_len, int *_new_length, int case_sensitivity, int *replace_count);
HIMOTEAPI char *himote_str_to_str(char *haystack, int length, char *needle,
		int needle_len, char *str, int str_len, int *_new_length);
HIMOTEAPI char *himote_trim(char *c, int len, char *what, int what_len, zval *return_value, int mode TSRMLS_DC);
HIMOTEAPI size_t himote_strip_tags(char *rbuf, int len, int *state, char *allow, int allow_len);
HIMOTEAPI size_t himote_strip_tags_ex(char *rbuf, int len, int *stateptr, char *allow, int allow_len, zend_bool allow_tag_spaces);
HIMOTEAPI int himote_char_to_str_ex(char *str, uint len, char from, char *to, int to_len, zval *result, int case_sensitivity, int *replace_count);
HIMOTEAPI int himote_char_to_str(char *str, uint len, char from, char *to, int to_len, zval *result);
HIMOTEAPI void himote_implode(zval *delim, zval *arr, zval *return_value TSRMLS_DC);
HIMOTEAPI void himote_explode(zval *delim, zval *str, zval *return_value, long limit);

HIMOTEAPI size_t himote_strspn(char *s1, char *s2, char *s1_end, char *s2_end); 
HIMOTEAPI size_t himote_strcspn(char *s1, char *s2, char *s1_end, char *s2_end); 

#ifndef HAVE_STRERROR
HIMOTEAPI char *himote_strerror(int errnum);
#define strerror himote_strerror
#endif

#ifndef HAVE_MBLEN
# define himote_mblen(ptr, len) 1
#else
# if defined(_REENTRANT) && defined(HAVE_MBRLEN) && defined(HAVE_MBSTATE_T)
#  define himote_mblen(ptr, len) ((ptr) == NULL ? mbsinit(&BG(mblen_state)): (int)mbrlen(ptr, len, &BG(mblen_state)))
# else
#  define himote_mblen(ptr, len) mblen(ptr, len)
# endif
#endif

void register_string_constants(INIT_FUNC_ARGS);

#endif /* HIMOTE_STRING_H */
