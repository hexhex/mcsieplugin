AUTOMAKE_OPTIONS = gnu

EXTRA_DIST =	mcsequilibriumtest.test

plugin_LTLIBRARIES = libdlvhexmcstestcontext1.la libdlvhexmcstestcontext2.la libdlvhexmcstestcontext3.la

libdlvhexmcstestcontext1_la_SOURCES = ./test1/TestContext1.cpp

AM_CPPFLAGS = \
 	-I$(top_srcdir)/include \
        $(BOOST_CPPFLAGS) \
 	$(DLVHEX_CFLAGS)
 
libdlvhexmcstestcontext1_la_LDFLAGS = -avoid-version -module \
 			     $(top_srcdir)/src/MCSequilibriumPlugin.lo \
                             $(top_srcdir)/src/Converter.lo \
                             $(top_srcdir)/src/BridgeRule.lo \
                             $(top_srcdir)/src/BridgeRuleEntry.lo \
                             $(top_srcdir)/src/ParseContext.lo \
 			     $(top_srcdir)/src/ACC_ContextAtom.lo \
			     $(top_srcdir)/src/DLV_ASP_ContextAtom.lo \
                             $(top_srcdir)/src/EquilibriumOutputBuilder.lo \
 			     $(top_srcdir)/src/EquilibriumPrintVisitor.lo

libdlvhexmcstestcontext2_la_SOURCES = ./test2/TestContext2.cpp

libdlvhexmcstestcontext2_la_LDFLAGS = -avoid-version -module \
 			     $(top_srcdir)/src/MCSequilibriumPlugin.lo \
                             $(top_srcdir)/src/Converter.lo \
                             $(top_srcdir)/src/BridgeRule.lo \
                             $(top_srcdir)/src/BridgeRuleEntry.lo \
                             $(top_srcdir)/src/ParseContext.lo \
 			     $(top_srcdir)/src/ACC_ContextAtom.lo \
			     $(top_srcdir)/src/DLV_ASP_ContextAtom.lo \
                             $(top_srcdir)/src/EquilibriumOutputBuilder.lo \
 			     $(top_srcdir)/src/EquilibriumPrintVisitor.lo

libdlvhexmcstestcontext3_la_SOURCES = ./test3/TestContext3.cpp

libdlvhexmcstestcontext3_la_LDFLAGS = -avoid-version -module \
 			     $(top_srcdir)/src/MCSequilibriumPlugin.lo \
                             $(top_srcdir)/src/Converter.lo \
                             $(top_srcdir)/src/BridgeRule.lo \
                             $(top_srcdir)/src/BridgeRuleEntry.lo \
                             $(top_srcdir)/src/ParseContext.lo \
 			     $(top_srcdir)/src/ACC_ContextAtom.lo \
			     $(top_srcdir)/src/DLV_ASP_ContextAtom.lo \
                             $(top_srcdir)/src/EquilibriumOutputBuilder.lo \
 			     $(top_srcdir)/src/EquilibriumPrintVisitor.lo
