AUTOMAKE_OPTIONS = gnu

lib_LTLIBRARIES = libldlvhexmcsdiagexpl.la
plugin_LTLIBRARIES = libdlvhexmcsdiagexpl.la

libldlvhexmcsdiagexpl_la_SOURCES = MCSdiagexplPlugin.cpp \
			     				QiConverter.cpp \
                             	BridgeRule.cpp \
                             	BridgeRuleEntry.cpp \
                             	ParseContext.cpp \
			     				ACC_ContextAtom.cpp \
			     				DLV_ASP_ContextAtom.cpp \
                             	EquilibriumOutputBuilder.cpp \
			     				EquilibriumPrintVisitor.cpp \
			     				DiagnosisPrintVisitor.cpp \
			     				Timing.cpp \
			     				Global.cpp

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
        $(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexmcsdiagexpl_la_SOURCES = 
libdlvhexmcsdiagexpl_la_LIBADD = -lldlvhexmcsdiagexpl
libdlvhexmcsdiagexpl_la_LDFLAGS = -avoid-version -module

