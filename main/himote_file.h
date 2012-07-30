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
   | Author: Rasmus Lerdorf <rasmus@lerdorf.on.ca>                        |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

/* Synced with himote 3.0 revision 1.30 1999-06-16 [ssb] */

#ifndef HIMOTE_FILE_H
#define HIMOTE_FILE_H

HIMOTE_MINIT_FUNCTION(file);
HIMOTE_MSHUTDOWN_FUNCTION(file);

HIMOTE_FUNCTION(tempnam);
HIMOTE_NAMED_FUNCTION(himote_if_tmpfile);
HIMOTE_NAMED_FUNCTION(himote_if_fopen);
HIMOTEAPI HIMOTE_FUNCTION(fclose);
HIMOTE_FUNCTION(popen);
HIMOTE_FUNCTION(pclose);
HIMOTEAPI HIMOTE_FUNCTION(feof);
HIMOTEAPI HIMOTE_FUNCTION(fread);
HIMOTEAPI HIMOTE_FUNCTION(fgetc);
HIMOTEAPI HIMOTE_FUNCTION(fgets);
HIMOTE_FUNCTION(fscanf);
HIMOTEAPI HIMOTE_FUNCTION(fgetss);
HIMOTE_FUNCTION(fgetcsv);
HIMOTE_FUNCTION(fputcsv);
HIMOTEAPI HIMOTE_FUNCTION(fwrite);
HIMOTEAPI HIMOTE_FUNCTION(fflush);
HIMOTEAPI HIMOTE_FUNCTION(rewind);
HIMOTEAPI HIMOTE_FUNCTION(ftell);
HIMOTEAPI HIMOTE_FUNCTION(fseek);
HIMOTE_FUNCTION(mkdir);
HIMOTE_FUNCTION(rmdir);
HIMOTEAPI HIMOTE_FUNCTION(fpassthru);
HIMOTE_FUNCTION(readfile);
HIMOTE_FUNCTION(umask);
HIMOTE_FUNCTION(rename);
HIMOTE_FUNCTION(unlink);
HIMOTE_FUNCTION(copy);
HIMOTE_FUNCTION(file);
HIMOTE_FUNCTION(file_get_contents);
HIMOTE_FUNCTION(file_put_contents);
HIMOTE_FUNCTION(get_meta_tags);
HIMOTE_FUNCTION(flock);
HIMOTE_FUNCTION(fd_set);
HIMOTE_FUNCTION(fd_isset);
#if (!defined(__BEOS__) && !defined(NETWARE) && HAVE_REALPATH) || defined(ZTS)
HIMOTE_FUNCTION(realpath);
#endif
#ifdef HAVE_FNMATCH
HIMOTE_FUNCTION(fnmatch);
#endif
HIMOTE_NAMED_FUNCTION(himote_if_ftruncate);
HIMOTE_NAMED_FUNCTION(himote_if_fstat);
HIMOTE_FUNCTION(sys_get_temp_dir);

HIMOTE_MINIT_FUNCTION(user_streams);

HIMOTEAPI int himote_le_stream_context(void);
HIMOTEAPI int himote_set_sock_blocking(int socketd, int block TSRMLS_DC);
HIMOTEAPI int himote_copy_file(char *src, char *dest TSRMLS_DC);
HIMOTEAPI int himote_copy_file_ex(char *src, char *dest, int src_chk TSRMLS_DC);
HIMOTEAPI int himote_copy_file_ctx(char *src, char *dest, int src_chk, himote_stream_context *context TSRMLS_DC);
HIMOTEAPI int himote_mkdir_ex(char *dir, long mode, int options TSRMLS_DC);
HIMOTEAPI int himote_mkdir(char *dir, long mode TSRMLS_DC);
HIMOTEAPI void himote_fgetcsv(himote_stream *stream, char delimiter, char enclosure, char escape_char, size_t buf_len, char *buf, zval *return_value TSRMLS_DC);

#define META_DEF_BUFSIZE 8192

#define HIMOTE_FILE_USE_INCLUDE_PATH 1
#define HIMOTE_FILE_IGNORE_NEW_LINES 2
#define HIMOTE_FILE_SKIP_EMPTY_LINES 4
#define HIMOTE_FILE_APPEND 8
#define HIMOTE_FILE_NO_DEFAULT_CONTEXT 16

typedef enum _himote_meta_tags_token {
	TOK_EOF = 0,
	TOK_OPENTAG,
	TOK_CLOSETAG,
	TOK_SLASH,
	TOK_EQUAL,
	TOK_SPACE,
	TOK_ID,
	TOK_STRING,
	TOK_OTHER
} himote_meta_tags_token;

typedef struct _himote_meta_tags_data {
	himote_stream *stream;
	int ulc;
	int lc;
	char *input_buffer;
	char *token_data;
	int token_len;
	int in_meta;
} himote_meta_tags_data;

himote_meta_tags_token himote_next_meta_token(himote_meta_tags_data * TSRMLS_DC);

typedef struct {
  	int pclose_ret;
	size_t def_chunk_size;
	long auto_detect_line_endings;
	long default_socket_timeout;
	char *user_agent; /* for the http wrapper */
	char *user_stream_current_filename; /* for simple recursion protection */
	himote_stream_context *default_context;
	HashTable *stream_wrappers;			/* per-request copy of url_stream_wrappers_hash */
	HashTable *stream_filters;			/* per-request copy of stream_filters_hash */
	HashTable *wrapper_errors;			/* key: wrapper address; value: linked list of char* */
} himote_file_globals;

#ifdef ZTS
#define FG(v) TSRMG(file_globals_id, himote_file_globals *, v)
extern HIMOTEAPI int file_globals_id;
#else
#define FG(v) (file_globals.v)
extern HIMOTEAPI himote_file_globals file_globals;
#endif


#endif /* HIMOTE_FILE_H */

