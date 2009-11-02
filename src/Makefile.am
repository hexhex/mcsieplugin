AUTOMAKE_OPTIONS = gnu

plugin_LTLIBRARIES = libdlvhexmcsequilibrium.la

libdlvhexmcsequilibrium_la_SOURCES = MCSequilibriumPlugin.cpp \
                             MCSequilibriumAtom.cpp \
                             MCSequilibriumConverter.cpp

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
        $(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexmcsequilibrium_la_LDFLAGS = -avoid-version -module

