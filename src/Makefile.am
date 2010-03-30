AUTOMAKE_OPTIONS = gnu

plugin_LTLIBRARIES = libdlvhexmcsdiagexpl.la

libdlvhexmcsdiagexpl_la_SOURCES = MCSdiagexplPlugin.cpp \
                             Converter.cpp \
			     QiConverter.cpp \
                             BridgeRule.cpp \
                             BridgeRuleEntry.cpp \
                             ParseContext.cpp \
			     ACC_ContextAtom.cpp \
			     DLV_ASP_ContextAtom.cpp \
                             EquilibriumOutputBuilder.cpp \
			     EquilibriumPrintVisitor.cpp \
			     Timing.cpp

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
        $(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexmcsdiagexpl_la_LDFLAGS = -avoid-version -module

