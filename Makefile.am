AM_CPPFLAGS = \
	-I$(top_srcdir)/src/libstrongswan \
	-I$(top_srcdir)/src/libcharon

AM_CFLAGS = \
	$(PLUGIN_CFLAGS)

if MONOLITHIC
noinst_LTLIBRARIES = libstrongswan-eap-20893-66666.la
else
plugin_LTLIBRARIES = libstrongswan-eap-20893-66666.la
endif

libstrongswan_eap_20893_66666_la_SOURCES = \
	eap_20893_66666_plugin.h eap_20893_66666_plugin.c eap_20893_66666.h eap_20893_66666.c

libstrongswan_eap_20893_66666_la_LDFLAGS = -module -avoid-version
