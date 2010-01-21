AUTOMAKE_OPTIONS = gnu

EXTRA_DIST = mcsequilibriumtests.test

plugin_LTLIBRARIES = 	libdlvhexmcstestcontext1.la\
			libdlvhexmcstestcontext2.la\
			libdlvhexmcstestcontext3.la\
			libdlvhexmcsbenchmark1.la\
			libdlvhexmcsbenchmark2.la\
			libdlvhexmcsbenchmark3.la\
			libdlvhexmcsbenchmark4.la\
			libdlvhexmcsbenchmark10.la

AM_CPPFLAGS = \
 	-I$(top_srcdir)/include \
        $(BOOST_CPPFLAGS) \
 	$(DLVHEX_CFLAGS)

libdlvhexmcstestcontext1_la_SOURCES = ./test1/TestContext1.cpp
libdlvhexmcstestcontext1_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/ACC_ContextAtom.lo

libdlvhexmcstestcontext2_la_SOURCES = ./test2/TestContext2.cpp
libdlvhexmcstestcontext2_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/ACC_ContextAtom.lo

libdlvhexmcstestcontext3_la_SOURCES = ./test3/TestContext3.cpp
libdlvhexmcstestcontext3_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/ACC_ContextAtom.lo

libdlvhexmcsbenchmark1_la_SOURCES = ./benchmark1/BenchContext1.cpp
libdlvhexmcsbenchmark1_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/ACC_ContextAtom.lo

libdlvhexmcsbenchmark2_la_SOURCES = ./benchmark2/BenchContext2.cpp
libdlvhexmcsbenchmark2_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/ACC_ContextAtom.lo

libdlvhexmcsbenchmark3_la_SOURCES = ./benchmark3/BenchContext3.cpp
libdlvhexmcsbenchmark3_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/ACC_ContextAtom.lo

libdlvhexmcsbenchmark4_la_SOURCES = ./benchmark4/BenchContext4.cpp
libdlvhexmcsbenchmark4_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/ACC_ContextAtom.lo

libdlvhexmcsbenchmark10_la_SOURCES = ./benchmark10/BenchContext10.cpp
libdlvhexmcsbenchmark10_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/ACC_ContextAtom.lo
