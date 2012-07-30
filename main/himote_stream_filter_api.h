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
   | Author: Wez Furlong <wez@thebrainroom.com>                           |
   | With suggestions from:                                               |
   |      Moriyoshi Koizumi <moriyoshi@at.wakwak.com>                     |
   |      Sara Golemon      <pollita@php.net>                             |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

/* The filter API works on the principle of "Bucket-Brigades".  This is
 * partially inspired by the Apache 2 method of doing things, although
 * it is intentially a light-weight implementation.
 *
 * Each stream can have a chain of filters for reading and another for writing.
 * 
 * When data is written to the stream, it is placed into a bucket and placed at
 * the start of the input brigade.
 *
 * The first filter in the chain is invoked on the brigade and (depending on
 * it's return value), the next filter is invoked and so on.
 * */

#define HIMOTE_STREAM_FILTER_READ	0x0001
#define HIMOTE_STREAM_FILTER_WRITE	0x0002
#define HIMOTE_STREAM_FILTER_ALL	(HIMOTE_STREAM_FILTER_READ | HIMOTE_STREAM_FILTER_WRITE)

typedef struct _himote_stream_bucket			himote_stream_bucket;
typedef struct _himote_stream_bucket_brigade	himote_stream_bucket_brigade;

struct _himote_stream_bucket {
	himote_stream_bucket *next, *prev;
	himote_stream_bucket_brigade *brigade;

	char *buf;
	size_t buflen;
	/* if non-zero, buf should be pefreed when the bucket is destroyed */
	int own_buf;
	int is_persistent;
	
	/* destroy this struct when refcount falls to zero */
	int refcount;
};

struct _himote_stream_bucket_brigade {
	himote_stream_bucket *head, *tail;
};

typedef enum {
	PSFS_ERR_FATAL,	/* error in data stream */
	PSFS_FEED_ME,	/* filter needs more data; stop processing chain until more is available */
	PSFS_PASS_ON	/* filter generated output buckets; pass them on to next in chain */
} himote_stream_filter_status_t;

/* Buckets API. */
BEGIN_EXTERN_C()
HIMOTEAPI himote_stream_bucket *himote_stream_bucket_new(himote_stream *stream, char *buf, size_t buflen, int own_buf, int buf_persistent TSRMLS_DC);
HIMOTEAPI int himote_stream_bucket_split(himote_stream_bucket *in, himote_stream_bucket **left, himote_stream_bucket **right, size_t length TSRMLS_DC);
HIMOTEAPI void himote_stream_bucket_delref(himote_stream_bucket *bucket TSRMLS_DC);
#define himote_stream_bucket_addref(bucket)	(bucket)->refcount++
HIMOTEAPI void himote_stream_bucket_prepend(himote_stream_bucket_brigade *brigade, himote_stream_bucket *bucket TSRMLS_DC);
HIMOTEAPI void himote_stream_bucket_append(himote_stream_bucket_brigade *brigade, himote_stream_bucket *bucket TSRMLS_DC);
HIMOTEAPI void himote_stream_bucket_unlink(himote_stream_bucket *bucket TSRMLS_DC);
HIMOTEAPI himote_stream_bucket *himote_stream_bucket_make_writeable(himote_stream_bucket *bucket TSRMLS_DC);
END_EXTERN_C()

#define PSFS_FLAG_NORMAL		0	/* regular read/write */
#define PSFS_FLAG_FLUSH_INC		1	/* an incremental flush */
#define PSFS_FLAG_FLUSH_CLOSE	2	/* final flush prior to closing */

typedef struct _himote_stream_filter_ops {

	himote_stream_filter_status_t (*filter)(
			himote_stream *stream,
			himote_stream_filter *thisfilter,
			himote_stream_bucket_brigade *buckets_in,
			himote_stream_bucket_brigade *buckets_out,
			size_t *bytes_consumed,
			int flags
			TSRMLS_DC);
	
	void (*dtor)(himote_stream_filter *thisfilter TSRMLS_DC);
	
	const char *label;
	
} himote_stream_filter_ops;

typedef struct _himote_stream_filter_chain {
	himote_stream_filter *head, *tail;

	/* Owning stream */
	himote_stream *stream;
} himote_stream_filter_chain;

struct _himote_stream_filter {
	himote_stream_filter_ops *fops;
	void *abstract; /* for use by filter implementation */
	himote_stream_filter *next;
	himote_stream_filter *prev;
	int is_persistent;

	/* link into stream and chain */
	himote_stream_filter_chain *chain;

	/* buffered buckets */
	himote_stream_bucket_brigade buffer;

	/* filters are auto_registered when they're applied */
	int rsrc_id;
};

/* stack filter onto a stream */
BEGIN_EXTERN_C()
HIMOTEAPI void _himote_stream_filter_prepend(himote_stream_filter_chain *chain, himote_stream_filter *filter TSRMLS_DC);
HIMOTEAPI int himote_stream_filter_prepend_ex(himote_stream_filter_chain *chain, himote_stream_filter *filter TSRMLS_DC);
HIMOTEAPI void _himote_stream_filter_append(himote_stream_filter_chain *chain, himote_stream_filter *filter TSRMLS_DC);
HIMOTEAPI int himote_stream_filter_append_ex(himote_stream_filter_chain *chain, himote_stream_filter *filter TSRMLS_DC);
HIMOTEAPI int _himote_stream_filter_flush(himote_stream_filter *filter, int finish TSRMLS_DC);
HIMOTEAPI himote_stream_filter *himote_stream_filter_remove(himote_stream_filter *filter, int call_dtor TSRMLS_DC);
HIMOTEAPI void himote_stream_filter_free(himote_stream_filter *filter TSRMLS_DC);
HIMOTEAPI himote_stream_filter *_himote_stream_filter_alloc(himote_stream_filter_ops *fops, void *abstract, int persistent STREAMS_DC TSRMLS_DC);
END_EXTERN_C()
#define himote_stream_filter_alloc(fops, thisptr, persistent) _himote_stream_filter_alloc((fops), (thisptr), (persistent) STREAMS_CC TSRMLS_CC)
#define himote_stream_filter_alloc_rel(fops, thisptr, persistent) _himote_stream_filter_alloc((fops), (thisptr), (persistent) STREAMS_REL_CC TSRMLS_CC)
#define himote_stream_filter_prepend(chain, filter) _himote_stream_filter_prepend((chain), (filter) TSRMLS_CC)
#define himote_stream_filter_append(chain, filter) _himote_stream_filter_append((chain), (filter) TSRMLS_CC)
#define himote_stream_filter_flush(filter, finish) _himote_stream_filter_flush((filter), (finish) TSRMLS_CC)

#define himote_stream_is_filtered(stream)	((stream)->readfilters.head || (stream)->writefilters.head)

typedef struct _himote_stream_filter_factory {
	himote_stream_filter *(*create_filter)(const char *filtername, zval *filterparams, int persistent TSRMLS_DC);
} himote_stream_filter_factory;

BEGIN_EXTERN_C()
HIMOTEAPI int himote_stream_filter_register_factory(const char *filterpattern, himote_stream_filter_factory *factory TSRMLS_DC);
HIMOTEAPI int himote_stream_filter_unregister_factory(const char *filterpattern TSRMLS_DC);
HIMOTEAPI int himote_stream_filter_register_factory_volatile(const char *filterpattern, himote_stream_filter_factory *factory TSRMLS_DC);
HIMOTEAPI himote_stream_filter *himote_stream_filter_create(const char *filtername, zval *filterparams, int persistent TSRMLS_DC);
END_EXTERN_C()

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
