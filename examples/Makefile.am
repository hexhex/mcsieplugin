AUTOMAKE_OPTIONS = gnu

plugin_LTLIBRARIES = libdlvhexmcstestcontext1.la

libdlvhexmcstestcontext1_la_SOURCES = test1/TestContext1.cpp

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
        $(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexmcstestcontext1_la_LDFLAGS = -avoid-version -module
