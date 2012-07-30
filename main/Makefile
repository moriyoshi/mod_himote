builddir=..
top_srcdir=/usr/share/httpd
top_builddir=/usr/share/httpd

LTLIBRARY_NAME = libhimotemain.la
LTLIBRARY_SOURCES = \
	alloca.c \
	fopen_wrappers.c \
	getopt.c \
	internal_functions.c \
	main.c \
	mergesort.c \
	network.c \
	output.c \
	himote_content_types.c \
	himote_ini.c \
	himote_logos.c \
	himote_open_temporary_file.c \
	himote_scandir.c \
	himote_sprintf.c \
	himote_ticks.c \
	himote_variables.c \
	reentrancy.c \
	rfc1867.c \
	SAPI.c \
	snprintf.c \
	spprintf.c \
	streams_cast.c \
	streams_filter.c \
	streams_glob_wrapper.c \
	streams_memory.c \
	streams_mmap.c \
	streams_plain_wrapper.c \
	streams.c \
	streams_transports.c \
	streams_userspace.c \
	streams_xp_socket.c \
	strlcat.c \
	strlcpy.c \
	string.c \
	basic_functions.c \
	array.c \
	assert.c \
	base64.c \
	crc32.c \
	credits.c \
	crypt.c \
	crypt_blowfish.c \
	crypt_freesec.c \
	crypt_sha256.c \
	crypt_sha512.c \
	css.c \
	cyr_convert.c \
	datetime.c \
	dir.c \
	dl.c \
	dns.c \
	exec.c \
	file.c \
	filestat.c \
	filters.c \
	flock_compat.c \
	formatted_print.c \
	fsock.c \
	ftok.c \
	ftp_fopen_wrapper.c \
	head.c \
	himote_crypt_r.c \
	himote_fopen_wrapper.c \
	html.c \
	http.c \
	http_fopen_wrapper.c \
	image.c \
	incomplete_class.c \
	info.c \
	iptc.c \
	lcg.c \
	levenshtein.c \
	link.c \
	link_win32.c \
	mail.c \
	math.c \
	md5.c \
	metaphone.c \
	microtime.c \
	pack.c \
	pageinfo.c \
	proc_open.c \
	quot_print.c \
	rand.c \
	scanf.c \
	sha1.c \
	soundex.c \
	streamsfuncs.c \
	strnatcmp.c \
	syslog.c \
	type.c \
	uniqid.c \
	url.c \
	url_scanner_ex.c \
	user_filters.c \
	uuencode.c \
	var.c \
	var_unserializer.c \
	versioning.c

TARGETS = $(LTLIBRARY_NAME)

include $(top_builddir)/build/rules.mk
include $(top_builddir)/build/library.mk

INCLUDES = -I$(builddir)/main -I$(builddir)/Zend -I$(builddir)/TSRM -I$(builddir)
