AUTOMAKE_OPTIONS = gnu

plugin_LTLIBRARIES = libdlvhexmcstestcontext1.la

libdlvhexmcstestcontext1_la_SOURCES = TestContext1.cpp

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
