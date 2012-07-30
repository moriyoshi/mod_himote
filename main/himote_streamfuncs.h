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
  | Authors: Wez Furlong <wez@thebrainroom.com>                          |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

/* Flags for stream_socket_client */
#define HIMOTE_STREAM_CLIENT_PERSISTENT	1
#define HIMOTE_STREAM_CLIENT_ASYNC_CONNECT	2
#define HIMOTE_STREAM_CLIENT_CONNECT		4

HIMOTE_FUNCTION(stream_socket_client);
HIMOTE_FUNCTION(stream_socket_server);
HIMOTE_FUNCTION(stream_socket_accept);
HIMOTE_FUNCTION(stream_socket_get_name);
HIMOTE_FUNCTION(stream_socket_recvfrom);
HIMOTE_FUNCTION(stream_socket_sendto);

HIMOTE_FUNCTION(stream_copy_to_stream);
HIMOTE_FUNCTION(stream_get_contents);

HIMOTE_FUNCTION(stream_set_blocking);
HIMOTE_FUNCTION(stream_select);
HIMOTE_FUNCTION(stream_set_timeout);
HIMOTE_FUNCTION(stream_set_read_buffer);
HIMOTE_FUNCTION(stream_set_write_buffer);
HIMOTE_FUNCTION(stream_get_transports);
HIMOTE_FUNCTION(stream_get_wrappers);
HIMOTE_FUNCTION(stream_get_line);
HIMOTE_FUNCTION(stream_get_meta_data);
HIMOTE_FUNCTION(stream_wrapper_register);
HIMOTE_FUNCTION(stream_wrapper_unregister);
HIMOTE_FUNCTION(stream_wrapper_restore);
HIMOTE_FUNCTION(stream_context_create);
HIMOTE_FUNCTION(stream_context_set_params);
HIMOTE_FUNCTION(stream_context_get_params);
HIMOTE_FUNCTION(stream_context_set_option);
HIMOTE_FUNCTION(stream_context_get_options);
HIMOTE_FUNCTION(stream_context_get_default);
HIMOTE_FUNCTION(stream_context_set_default);
HIMOTE_FUNCTION(stream_filter_prepend);
HIMOTE_FUNCTION(stream_filter_append);
HIMOTE_FUNCTION(stream_filter_remove);
HIMOTE_FUNCTION(stream_socket_enable_crypto);
HIMOTE_FUNCTION(stream_socket_shutdown);
HIMOTE_FUNCTION(stream_resolve_include_path);
HIMOTE_FUNCTION(stream_is_local);
HIMOTE_FUNCTION(stream_supports_lock);

#if HAVE_SOCKETPAIR
HIMOTE_FUNCTION(stream_socket_pair);
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

