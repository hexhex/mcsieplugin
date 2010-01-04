AUTOMAKE_OPTIONS = gnu

plugin_LTLIBRARIES = libdlvhexmcsequilibrium.la

libdlvhexmcsequilibrium_la_SOURCES = PluginImport.cpp \
			     MCSequilibriumPlugin.cpp \
                             Converter.cpp \
                             BridgeRule.cpp \
                             BridgeRuleEntry.cpp \
                             ParseContext.cpp \
			     ACC_ContextAtom.cpp \
			     DLV_ASP_ContextAtom.cpp \
                             EquilibriumOutputBuilder.cpp \
			     EquilibriumPrintVisitor.cpp

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
        $(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexmcsequilibrium_la_LDFLAGS = -avoid-version -module

