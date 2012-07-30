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

#ifndef HIMOTE3_COMPAT_H
#define HIMOTE3_COMPAT_H

typedef zval pval;

#define pval_copy_constructor zval_copy_ctor
#define pval_destructor	zval_dtor

#define _himote3_hash_init zend_hash_init
#define _himote3_hash_destroy zend_hash_destroy

#define _himote3_hash_clean zend_hash_clean

#define _himote3_hash_add_or_update zend_hash_add_or_update
#define _himote3_hash_add zend_hash_add
#define _himote3_hash_update zend_hash_update

#define _himote3_hash_quick_add_or_update zend_hash_quick_add_or_update
#define _himote3_hash_quick_add zend_hash_quick_add
#define _himote3_hash_quick_update zend_hash_quick_update

#define _himote3_hash_index_update_or_next_insert zend_hash_index_update_or_next_insert
#define _himote3_hash_index_update zend_hash_index_update
#define _himote3_hash_next_index_insert zend_hash_next_index_insert

#define _himote3_hash_pointer_update zend_hash_pointer_update

#define _himote3_hash_pointer_index_update_or_next_insert zend_hash_pointer_index_update_or_next_insert
#define _himote3_hash_pointer_index_update zend_hash_pointer_index_update
#define _himote3_hash_next_index_pointer_update zend_hash_next_index_pointer_update
#define _himote3_hash_next_index_pointer_insert zend_hash_next_index_pointer_insert

#define _himote3_hash_del_key_or_index zend_hash_del_key_or_index
#define _himote3_hash_del zend_hash_del
#define _himote3_hash_index_del zend_hash_index_del

#define _himote3_hash_find zend_hash_find
#define _himote3_hash_quick_find zend_hash_quick_find
#define _himote3_hash_index_find zend_hash_index_find

#define _himote3_hash_exists zend_hash_exists
#define _himote3_hash_index_exists zend_hash_index_exists
#define _himote3_hash_is_pointer zend_hash_is_pointer
#define _himote3_hash_index_is_pointer zend_hash_index_is_pointer
#define _himote3_hash_next_free_element zend_hash_next_free_element

#define _himote3_hash_move_forward zend_hash_move_forward
#define _himote3_hash_move_backwards zend_hash_move_backwards
#define _himote3_hash_get_current_key zend_hash_get_current_key
#define _himote3_hash_get_current_data zend_hash_get_current_data
#define _himote3_hash_internal_pointer_reset zend_hash_internal_pointer_reset
#define _himote3_hash_internal_pointer_end zend_hash_internal_pointer_end

#define _himote3_hash_copy zend_hash_copy
#define _himote3_hash_merge zend_hash_merge
#define _himote3_hash_sort zend_hash_sort
#define _himote3_hash_minmax zend_hash_minmax

#define _himote3_hash_num_elements zend_hash_num_elements

#define _himote3_hash_apply zend_hash_apply
#define _himote3_hash_apply_with_argument zend_hash_apply_with_argument


#define himote3_error himote_error

#define himote3_printf himote_printf
#define _himote3_sprintf himote_sprintf



#define himote3_module_entry zend_module_entry

#define himote3_strndup		zend_strndup
#define himote3_str_tolower	zend_str_tolower
#define himote3_binary_strcmp	zend_binary_strcmp


#define himote3_list_insert	zend_list_insert
#define himote3_list_find		zend_list_find
#define himote3_list_delete	zend_list_delete

#define himote3_plist_insert	zend_plist_insert
#define himote3_plist_find		zend_plist_find
#define himote3_plist_delete	zend_plist_delete

#define zend_print_pval		zend_print_zval
#define zend_print_pval_r	zend_print_zval_r


#define function_entry		zend_function_entry

#define _himote3_addslashes	himote_addslashes
#define _himote3_stripslashes	himote_stripslashes
#define himote3_dl             himote_dl

#define getParameters		zend_get_parameters
#define getParametersArray	zend_get_parameters_array

#define list_entry			zend_rsrc_list_entry

#endif							/* HIMOTE3_COMPAT_H */
