lib_LTLIBRARIES = libldlvhexmcsdiagexpl.la
plugin_LTLIBRARIES = libdlvhexmcsdiagexpl.la

libldlvhexmcsdiagexpl_la_SOURCES = InputConverter.cpp \
                                   BridgeRule.cpp \
                                   BridgeRuleEntry.cpp \
                                   ParseContext.cpp \
                                   ACC_ContextAtom.cpp \
                                   DLV_ASP_ContextAtom.cpp \
                                   OutputRewriter.cpp \
                                   EquilibriumPrintVisitor.cpp \
                                   DiagExplPrintVisitor.cpp \
                                   Timing.cpp \
                                   Global.cpp

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
        $(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexmcsdiagexpl_la_SOURCES = MCSdiagexplPlugin.cpp
libdlvhexmcsdiagexpl_la_LDFLAGS = -avoid-version -module
libdlvhexmcsdiagexpl_la_LIBADD = libldlvhexmcsdiagexpl.la

