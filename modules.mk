SUBDIRS = Zend TSRM main

mod_himote.la: mod_himote.slo sapi_apache2.slo himote_functions.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version mod_himote.lo sapi_apache2.lo himote_functions.lo Zend/libzend.la TSRM/libtsrm.la main/libhimotemain.la

DISTCLEAN_TARGETS = modules.mk
shared =  mod_himote.la

