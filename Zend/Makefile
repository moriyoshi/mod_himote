builddir=..
top_srcdir=/usr/share/httpd
top_builddir=/usr/share/httpd



RE2C = re2c
RE2C_FLAGS = 

LTLIBRARY_NAME = libzend.la
LTLIBRARY_SOURCES = \
	zend.c \
	zend_alloc.c \
	zend_API.c \
	zend_builtin_functions.c \
	zend_closures.c \
	zend_compile.c \
	zend_constants.c \
	zend_default_classes.c \
	zend_dynamic_array.c \
	zend_exceptions.c \
	zend_execute.c \
	zend_execute_API.c \
	zend_extensions.c \
	zend_float.c \
	zend_gc.c \
	zend_hash.c \
	zend_highlight.c \
	zend_indent.c \
	zend_ini.c \
	zend_ini_parser.c \
	zend_ini_scanner.c \
	zend_interfaces.c \
	zend_iterators.c \
	zend_language_parser.c \
	zend_language_scanner.c \
	zend_list.c \
	zend_llist.c \
	zend_multibyte.c \
	zend_object_handlers.c \
	zend_objects.c \
	zend_objects_API.c \
	zend_opcode.c \
	zend_operators.c \
	zend_ptr_stack.c \
	zend_qsort.c \
	zend_sprintf.c \
	zend_stack.c \
	zend_stream.c \
	zend_strtod.c \
	zend_ts_hash.c \
	zend_variables.c

TARGETS = $(LTLIBRARY_NAME)

include $(top_builddir)/build/rules.mk
include $(top_builddir)/build/library.mk

INCLUDES = -I$(builddir)/main -I$(builddir)/Zend -I$(builddir)/TSRM

zend_language_scanner.c: zend_language_scanner.l
	@($(RE2C) $(RE2C_FLAGS) --case-inverted -cbdFt zend_language_scanner_defs.h -ozend_language_scanner.c zend_language_scanner.l)

zend_ini_scanner.c: zend_ini_scanner.l
	@($(RE2C) $(RE2C_FLAGS) --case-inverted -cbdFt zend_ini_scanner_defs.h -ozend_ini_scanner.c zend_ini_scanner.l)

zend_language_parser.h: zend_language_parser.c
zend_language_parser.c: zend_language_parser.y
	@$(YACC) -p zend -v -d zend_language_parser.y -o $@

zend_ini_parser.h: zend_ini_parser.c
zend_ini_parser.c: zend_ini_parser.y
	@$(YACC) -p ini_ -v -d zend_ini_parser.y -o $@

