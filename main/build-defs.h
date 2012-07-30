/*                                                                -*- C -*-
   +----------------------------------------------------------------------+
   | HIMOTE Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2007 The HIMOTE Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the HIMOTE license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.himote.net/license/3_01.txt                                  |
   | If you did not receive a copy of the HIMOTE license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Stig Sæther Bakken <ssb@php.net>                             |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#define CONFIGURE_COMMAND " './configure'  '--enable-debug' '--with-gd' '--with-curl' '--with-jpeg-dir=/usr/X11/' '--with-png-dir=/usr/X11' '--enable-gd-native-ttf' '--with-zlib' '--enable-calendar' '--enable-mbstring' '--with-openssl' '--enable-pdo' '--enable-dba' '--enable-pcntl' '--with-pdo-mysql=mysqlnd' '--with-mysqli=mysqlnd' '--with-mysql=mysqlnd' '--with-mysql-sock=/var/lib/mysql/mysql.sock' '--with-db4=/Users/moriyoshi/opt/db-4.8.30' '--prefix=/Users/moriyoshi/opt/himote-5.3'"
#define HIMOTE_ADA_INCLUDE		""
#define HIMOTE_ADA_LFLAGS		""
#define HIMOTE_ADA_LIBS		""
#define HIMOTE_APACHE_INCLUDE	""
#define HIMOTE_APACHE_TARGET	""
#define HIMOTE_FHTTPD_INCLUDE      ""
#define HIMOTE_FHTTPD_LIB          ""
#define HIMOTE_FHTTPD_TARGET       ""
#define HIMOTE_CFLAGS		"$(CFLAGS_CLEAN) -prefer-non-pic -static"
#define HIMOTE_DBASE_LIB		""
#define HIMOTE_BUILD_DEBUG		" -Wall"
#define HIMOTE_GDBM_INCLUDE	""
#define HIMOTE_IBASE_INCLUDE	""
#define HIMOTE_IBASE_LFLAGS	""
#define HIMOTE_IBASE_LIBS		""
#define HIMOTE_IFX_INCLUDE		""
#define HIMOTE_IFX_LFLAGS		""
#define HIMOTE_IFX_LIBS		""
#define HIMOTE_INSTALL_IT		"@echo "Installing HIMOTE CGI binary: $(INSTALL_ROOT)$(bindir)/"; $(INSTALL) -m 0755 $(SAPI_CGI_PATH) $(INSTALL_ROOT)$(bindir)/$(program_prefix)himote-cgi$(program_suffix)$(EXEEXT)"
#define HIMOTE_IODBC_INCLUDE	""
#define HIMOTE_IODBC_LFLAGS	""
#define HIMOTE_IODBC_LIBS		""
#define HIMOTE_MSQL_INCLUDE	""
#define HIMOTE_MSQL_LFLAGS		""
#define HIMOTE_MSQL_LIBS		""
#define HIMOTE_MYSQL_INCLUDE	""
#define HIMOTE_MYSQL_LIBS		""
#define HIMOTE_MYSQL_TYPE		""
#define HIMOTE_ODBC_INCLUDE	""
#define HIMOTE_ODBC_LFLAGS		""
#define HIMOTE_ODBC_LIBS		""
#define HIMOTE_ODBC_TYPE		""
#define HIMOTE_OCI8_SHARED_LIBADD 	""
#define HIMOTE_OCI8_DIR			""
#define HIMOTE_OCI8_ORACLE_VERSION		""
#define HIMOTE_ORACLE_SHARED_LIBADD 	"@ORACLE_SHARED_LIBADD@"
#define HIMOTE_ORACLE_DIR				"@ORACLE_DIR@"
#define HIMOTE_ORACLE_VERSION			"@ORACLE_VERSION@"
#define HIMOTE_PGSQL_INCLUDE	""
#define HIMOTE_PGSQL_LFLAGS	""
#define HIMOTE_PGSQL_LIBS		""
#define HIMOTE_PROG_SENDMAIL	"/usr/sbin/sendmail"
#define HIMOTE_SOLID_INCLUDE	""
#define HIMOTE_SOLID_LIBS		""
#define HIMOTE_EMPRESS_INCLUDE	""
#define HIMOTE_EMPRESS_LIBS	""
#define HIMOTE_SYBASE_INCLUDE	""
#define HIMOTE_SYBASE_LFLAGS	""
#define HIMOTE_SYBASE_LIBS		""
#define HIMOTE_DBM_TYPE		""
#define HIMOTE_DBM_LIB		""
#define HIMOTE_LDAP_LFLAGS		""
#define HIMOTE_LDAP_INCLUDE	""
#define HIMOTE_LDAP_LIBS		""
#define HIMOTE_BIRDSTEP_INCLUDE     ""
#define HIMOTE_BIRDSTEP_LIBS        ""
#define PEAR_INSTALLDIR         "/Users/moriyoshi/opt/himote-5.3/lib/himote"
#define HIMOTE_INCLUDE_PATH	".:/Users/moriyoshi/opt/himote-5.3/lib/himote"
#define HIMOTE_EXTENSION_DIR       "/Users/moriyoshi/opt/himote-5.3/lib/himote/extensions/debug-non-zts-20090626"
#define HIMOTE_PREFIX              "/Users/moriyoshi/opt/himote-5.3"
#define HIMOTE_BINDIR              "/Users/moriyoshi/opt/himote-5.3/bin"
#define HIMOTE_SBINDIR             "/Users/moriyoshi/opt/himote-5.3/sbin"
#define HIMOTE_MANDIR              "/Users/moriyoshi/opt/himote-5.3/man"
#define HIMOTE_LIBDIR              "/Users/moriyoshi/opt/himote-5.3/lib/himote"
#define HIMOTE_DATADIR             "/Users/moriyoshi/opt/himote-5.3/share/himote"
#define HIMOTE_SYSCONFDIR          "/Users/moriyoshi/opt/himote-5.3/etc"
#define HIMOTE_LOCALSTATEDIR       "/Users/moriyoshi/opt/himote-5.3/var"
#define HIMOTE_CONFIG_FILE_PATH    "/Users/moriyoshi/opt/himote-5.3/lib"
#define HIMOTE_CONFIG_FILE_SCAN_DIR    ""
#define HIMOTE_SHLIB_SUFFIX        "so"
