builddir=..
top_srcdir=/usr/share/httpd
top_builddir=/usr/share/httpd

LTLIBRARY_NAME = libtsrm.la
LTLIBRARY_SOURCES = \
	TSRM.c \
	tsrm_strtok_r.c \
	tsrm_virtual_cwd.c

TARGETS = $(LTLIBRARY_NAME)

include $(top_builddir)/build/rules.mk
include $(top_builddir)/build/library.mk

INCLUDES = -I$(builddir)/main -I$(builddir)/Zend -I$(builddir)/TSRM
