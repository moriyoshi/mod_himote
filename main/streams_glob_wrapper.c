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
   | Authors: Marcus Boerger <helly@php.net>                              |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#include "himote.h"
#include "himote_streams_int.h"

#ifdef HAVE_GLOB
# ifndef HIMOTE_WIN32
#  include <glob.h>
# else
#  include "win32/glob.h"
# endif
#endif

#ifdef HAVE_GLOB
#ifndef GLOB_ONLYDIR
#define GLOB_ONLYDIR (1<<30)
#define GLOB_FLAGMASK (~GLOB_ONLYDIR)
#else
#define GLOB_FLAGMASK (~0)
#endif

typedef struct {
	glob_t   glob;
	size_t   index;
	int      flags;
	char     *path;
	size_t   path_len;
	char     *pattern;
	size_t   pattern_len;
} glob_s_t;

HIMOTEAPI char* _himote_glob_stream_get_path(himote_stream *stream, int copy, int *plen STREAMS_DC TSRMLS_DC) /* {{{ */
{
	glob_s_t *pglob = (glob_s_t *)stream->abstract;

	if (pglob && pglob->path) {
		if (plen) {
			*plen = pglob->path_len;
		}
		if (copy) {
			return estrndup(pglob->path, pglob->path_len);
		} else {
			return pglob->path;
		}
	} else {
		if (plen) {
			*plen = 0;
		}
		return NULL;
	}
}
/* }}} */

HIMOTEAPI char* _himote_glob_stream_get_pattern(himote_stream *stream, int copy, int *plen STREAMS_DC TSRMLS_DC) /* {{{ */
{
	glob_s_t *pglob = (glob_s_t *)stream->abstract;
	
	if (pglob && pglob->pattern) {
		if (plen) {
			*plen = pglob->pattern_len;
		}
		if (copy) {
			return estrndup(pglob->pattern, pglob->pattern_len);
		} else {
			return pglob->pattern;
		}
	} else {
		if (plen) {
			*plen = 0;
		}
		return NULL;
	}
}
/* }}} */

HIMOTEAPI int _himote_glob_stream_get_count(himote_stream *stream, int *pflags STREAMS_DC TSRMLS_DC) /* {{{ */
{
	glob_s_t *pglob = (glob_s_t *)stream->abstract;

	if (pglob) {
		if (pflags) {
			*pflags = pglob->flags;
		}
		return pglob->glob.gl_pathc;
	} else {
		if (pflags) {
			*pflags = 0;
		}
		return 0;
	}
}
/* }}} */

static void himote_glob_stream_path_split(glob_s_t *pglob, char *path, int get_path, char **p_file TSRMLS_DC) /* {{{ */
{
	char *pos, *gpath = path;

	if ((pos = strrchr(path, '/')) != NULL) {
		path = pos+1;
	}
#if defined(HIMOTE_WIN32) || defined(NETWARE)
	if ((pos = strrchr(path, '\\')) != NULL) {
		path = pos+1;
	}
#endif

	*p_file = path;

	if (get_path) {
		if (pglob->path) {
			efree(pglob->path);
		}
		if (path != gpath) {
			path--;
		}
		pglob->path_len = path - gpath;
		pglob->path = estrndup(gpath, pglob->path_len);
	}
}
/* }}} */

static size_t himote_glob_stream_read(himote_stream *stream, char *buf, size_t count TSRMLS_DC) /* {{{ */
{
	glob_s_t *pglob = (glob_s_t *)stream->abstract;
	himote_stream_dirent *ent = (himote_stream_dirent*)buf;
	char *path;

	/* avoid problems if someone mis-uses the stream */
	if (count == sizeof(himote_stream_dirent) && pglob) {
		if (pglob->index < pglob->glob.gl_pathc) {
			himote_glob_stream_path_split(pglob, pglob->glob.gl_pathv[pglob->index++], pglob->flags & GLOB_APPEND, &path TSRMLS_CC);
			HIMOTE_STRLCPY(ent->d_name, path, sizeof(ent->d_name), strlen(path));
			return sizeof(himote_stream_dirent);
		}
		pglob->index = pglob->glob.gl_pathc;
		if (pglob->path) {
			efree(pglob->path);
			pglob->path = NULL;
		}
	}

	return 0;
}
/* }}} */

static int himote_glob_stream_close(himote_stream *stream, int close_handle TSRMLS_DC)  /* {{{ */
{
	glob_s_t *pglob = (glob_s_t *)stream->abstract;

	if (pglob) {
		pglob->index = 0;
		globfree(&pglob->glob);
		if (pglob->path) {
			efree(pglob->path);
		}
		if (pglob->pattern) {
			efree(pglob->pattern);
		}
	}
	efree(stream->abstract);
	return 0;
}
/* {{{ */

static int himote_glob_stream_rewind(himote_stream *stream, off_t offset, int whence, off_t *newoffs TSRMLS_DC) /* {{{ */
{
	glob_s_t *pglob = (glob_s_t *)stream->abstract;

	if (pglob) {
		pglob->index = 0;
		if (pglob->path) {
			efree(pglob->path);
			pglob->path = NULL;
		}
	}
	return 0;
}
/* }}} */

himote_stream_ops  himote_glob_stream_ops = {
	NULL, himote_glob_stream_read,
	himote_glob_stream_close, NULL,
	"glob",
	himote_glob_stream_rewind,
	NULL, /* cast */
	NULL, /* stat */
	NULL  /* set_option */
};

 /* {{{ himote_glob_stream_opener */
static himote_stream *himote_glob_stream_opener(himote_stream_wrapper *wrapper, char *path, char *mode,
		int options, char **opened_path, himote_stream_context *context STREAMS_DC TSRMLS_DC)
{
	glob_s_t *pglob;
	int ret;
	char *tmp, *pos;

	if (((options & STREAM_DISABLE_OPEN_BASEDIR) == 0) && himote_check_open_basedir(path TSRMLS_CC)) {
		return NULL;
	}

	if (!strncmp(path, "glob://", sizeof("glob://")-1)) {
		path += sizeof("glob://")-1;
		if (opened_path) {
			*opened_path = estrdup(path);
		}
	}

	pglob = ecalloc(sizeof(*pglob), 1);
	
	if (0 != (ret = glob(path, pglob->flags & GLOB_FLAGMASK, NULL, &pglob->glob))) {
#ifdef GLOB_NOMATCH
		if (GLOB_NOMATCH != ret)
#endif
		{
			efree(pglob);
			return NULL;
		}
	}

	pos = path;
	if ((tmp = strrchr(pos, '/')) != NULL) {
		pos = tmp+1;
	}
#if defined(HIMOTE_WIN32) || defined(NETWARE)
	if ((tmp = strrchr(pos, '\\')) != NULL) {
		pos = tmp+1;
	}
#endif

	pglob->pattern_len = strlen(pos);
	pglob->pattern = estrndup(pos, pglob->pattern_len);

	pglob->flags |= GLOB_APPEND;

	if (pglob->glob.gl_pathc) {
		himote_glob_stream_path_split(pglob, pglob->glob.gl_pathv[0], 1, &tmp TSRMLS_CC);
	} else {
		himote_glob_stream_path_split(pglob, path, 1, &tmp TSRMLS_CC);
	}

	return himote_stream_alloc(&himote_glob_stream_ops, pglob, 0, mode);
}
/* }}} */

static himote_stream_wrapper_ops  himote_glob_stream_wrapper_ops = {
	NULL,
	NULL,
	NULL,
	NULL,
	himote_glob_stream_opener,
	"glob",
	NULL,
	NULL,
	NULL,
	NULL
};

himote_stream_wrapper  himote_glob_stream_wrapper = {
	&himote_glob_stream_wrapper_ops,
	NULL,
	0
};
#endif /* HAVE_GLOB */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
