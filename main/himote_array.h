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
   | Authors: Andi Gutmans <andi@zend.com>                                |
   |          Zeev Suraski <zeev@zend.com>                                |
   |          Rasmus Lerdorf <rasmus@php.net>                             |
   |          Andrei Zmievski <andrei@php.net>                            |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_ARRAY_H
#define HIMOTE_ARRAY_H

HIMOTE_MINIT_FUNCTION(array);
HIMOTE_MSHUTDOWN_FUNCTION(array);

HIMOTE_FUNCTION(ksort);
HIMOTE_FUNCTION(krsort);
HIMOTE_FUNCTION(natsort);
HIMOTE_FUNCTION(natcasesort);
HIMOTE_FUNCTION(asort);
HIMOTE_FUNCTION(arsort);
HIMOTE_FUNCTION(sort);
HIMOTE_FUNCTION(rsort);
HIMOTE_FUNCTION(usort);
HIMOTE_FUNCTION(uasort);
HIMOTE_FUNCTION(uksort);
HIMOTE_FUNCTION(array_walk);
HIMOTE_FUNCTION(array_walk_recursive);
HIMOTE_FUNCTION(count);
HIMOTE_FUNCTION(end);
HIMOTE_FUNCTION(prev);
HIMOTE_FUNCTION(next);
HIMOTE_FUNCTION(reset);
HIMOTE_FUNCTION(current);
HIMOTE_FUNCTION(key);
HIMOTE_FUNCTION(min);
HIMOTE_FUNCTION(max);
HIMOTE_FUNCTION(in_array);
HIMOTE_FUNCTION(array_search);
HIMOTE_FUNCTION(extract);
HIMOTE_FUNCTION(compact);
HIMOTE_FUNCTION(array_fill);
HIMOTE_FUNCTION(array_fill_keys);
HIMOTE_FUNCTION(range);
HIMOTE_FUNCTION(shuffle);
HIMOTE_FUNCTION(array_multisort);
HIMOTE_FUNCTION(array_push);
HIMOTE_FUNCTION(array_pop);
HIMOTE_FUNCTION(array_shift);
HIMOTE_FUNCTION(array_unshift);
HIMOTE_FUNCTION(array_splice);
HIMOTE_FUNCTION(array_slice);
HIMOTE_FUNCTION(array_merge);
HIMOTE_FUNCTION(array_merge_recursive);
HIMOTE_FUNCTION(array_replace);
HIMOTE_FUNCTION(array_replace_recursive);
HIMOTE_FUNCTION(array_keys);
HIMOTE_FUNCTION(array_values);
HIMOTE_FUNCTION(array_count_values);
HIMOTE_FUNCTION(array_reverse);
HIMOTE_FUNCTION(array_reduce);
HIMOTE_FUNCTION(array_pad);
HIMOTE_FUNCTION(array_flip);
HIMOTE_FUNCTION(array_change_key_case);
HIMOTE_FUNCTION(array_rand);
HIMOTE_FUNCTION(array_unique);
HIMOTE_FUNCTION(array_intersect);
HIMOTE_FUNCTION(array_intersect_key);
HIMOTE_FUNCTION(array_intersect_ukey);
HIMOTE_FUNCTION(array_uintersect);
HIMOTE_FUNCTION(array_intersect_assoc);
HIMOTE_FUNCTION(array_uintersect_assoc);
HIMOTE_FUNCTION(array_intersect_uassoc);
HIMOTE_FUNCTION(array_uintersect_uassoc);
HIMOTE_FUNCTION(array_diff);
HIMOTE_FUNCTION(array_diff_key);
HIMOTE_FUNCTION(array_diff_ukey);
HIMOTE_FUNCTION(array_udiff);
HIMOTE_FUNCTION(array_diff_assoc);
HIMOTE_FUNCTION(array_udiff_assoc);
HIMOTE_FUNCTION(array_diff_uassoc);
HIMOTE_FUNCTION(array_udiff_uassoc);
HIMOTE_FUNCTION(array_sum);
HIMOTE_FUNCTION(array_product);
HIMOTE_FUNCTION(array_filter);
HIMOTE_FUNCTION(array_map);
HIMOTE_FUNCTION(array_key_exists);
HIMOTE_FUNCTION(array_chunk);
HIMOTE_FUNCTION(array_combine);

HIMOTEAPI HashTable* php_splice(HashTable *, int, int, zval ***, int, HashTable **);
HIMOTEAPI int php_array_merge(HashTable *dest, HashTable *src, int recursive TSRMLS_DC);
HIMOTEAPI int php_array_replace_recursive(HashTable *dest, HashTable *src TSRMLS_DC);
HIMOTEAPI int php_multisort_compare(const void *a, const void *b TSRMLS_DC);

#define HIMOTE_SORT_REGULAR            0
#define HIMOTE_SORT_NUMERIC            1
#define HIMOTE_SORT_STRING             2
#define HIMOTE_SORT_DESC               3
#define HIMOTE_SORT_ASC                4
#define HIMOTE_SORT_LOCALE_STRING      5

ZEND_BEGIN_MODULE_GLOBALS(array) 
	int *multisort_flags[2];
	int (*compare_func)(zval *result, zval *op1, zval *op2 TSRMLS_DC);
ZEND_END_MODULE_GLOBALS(array) 

#ifdef ZTS
#define ARRAYG(v) TSRMG(array_globals_id, zend_array_globals *, v)
#else
#define ARRAYG(v) (array_globals.v)
#endif

#endif /* HIMOTE_ARRAY_H */
