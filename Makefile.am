AM_CPPFLAGS = \
	-I$(top_srcdir)/src/libstrongswan \
	-I$(top_srcdir)/src/libcharon

AM_CFLAGS = \
	$(PLUGIN_CFLAGS)

AM_LDFLAGS = \
	-lrt

if MONOLITHIC
noinst_LTLIBRARIES = libstrongswan-eap-5g.la
else
plugin_LTLIBRARIES = libstrongswan-eap-5g.la
endif

libstrongswan_eap_5g_la_SOURCES = \
	eap_5g_plugin.h eap_5g_plugin.c eap_5g.h eap_5g.c

libstrongswan_eap_5g_la_LDFLAGS = -module -avoid-version -lrt