AUTOMAKE_OPTIONS = gnu

EXTRA_DIST =mcsequilibriumtests.test

plugin_LTLIBRARIES = libdlvhexmcstestcontext1.la libdlvhexmcstestcontext2.la libdlvhexmcstestcontext3.la

libdlvhexmcstestcontext1_la_SOURCES = ./test1/TestContext1.cpp

AM_CPPFLAGS = \
 	-I$(top_srcdir)/include \
        $(BOOST_CPPFLAGS) \
 	$(DLVHEX_CFLAGS)
 
libdlvhexmcstestcontext1_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/MCSequilibriumPlugin.lo \
                             $(top_builddir)/src/Converter.lo \
                             $(top_builddir)/src/BridgeRule.lo \
                             $(top_builddir)/src/BridgeRuleEntry.lo \
                             $(top_builddir)/src/ParseContext.lo \
 			     $(top_builddir)/src/ACC_ContextAtom.lo \
			     $(top_builddir)/src/DLV_ASP_ContextAtom.lo \
                             $(top_builddir)/src/EquilibriumOutputBuilder.lo \
 			     $(top_builddir)/src/EquilibriumPrintVisitor.lo

libdlvhexmcstestcontext2_la_SOURCES = ./test2/TestContext2.cpp

libdlvhexmcstestcontext2_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/MCSequilibriumPlugin.lo \
                             $(top_builddir)/src/Converter.lo \
                             $(top_builddir)/src/BridgeRule.lo \
                             $(top_builddir)/src/BridgeRuleEntry.lo \
                             $(top_builddir)/src/ParseContext.lo \
 			     $(top_builddir)/src/ACC_ContextAtom.lo \
			     $(top_builddir)/src/DLV_ASP_ContextAtom.lo \
                             $(top_builddir)/src/EquilibriumOutputBuilder.lo \
 			     $(top_builddir)/src/EquilibriumPrintVisitor.lo

libdlvhexmcstestcontext3_la_SOURCES = ./test3/TestContext3.cpp

libdlvhexmcstestcontext3_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/MCSequilibriumPlugin.lo \
                             $(top_builddir)/src/Converter.lo \
                             $(top_builddir)/src/BridgeRule.lo \
                             $(top_builddir)/src/BridgeRuleEntry.lo \
                             $(top_builddir)/src/ParseContext.lo \
 			     $(top_builddir)/src/ACC_ContextAtom.lo \
			     $(top_builddir)/src/DLV_ASP_ContextAtom.lo \
                             $(top_builddir)/src/EquilibriumOutputBuilder.lo \
 			     $(top_builddir)/src/EquilibriumPrintVisitor.lo
