AUTOMAKE_OPTIONS = gnu

EXTRA_DIST = mcsequilibriumtests.test

plugin_LTLIBRARIES = 	libdlvhexmcstestcontext1.la\
			libdlvhexmcstestcontext2.la\
			libdlvhexmcstestcontext3.la\
			libdlvhexmcsbenchmark1.la\
			libdlvhexmcsbenchmark2.la\
			libdlvhexmcsbenchmark3.la\
			libdlvhexmcsbenchmark4.la\
			libdlvhexmcsbenchmark5.la\
			libdlvhexmcsbenchmark6.la\
			libdlvhexmcsbenchmark7.la\
			libdlvhexmcsbenchmark8.la\
			libdlvhexmcsbenchmark9.la\
			libdlvhexmcsbenchmark10.la\
			libdlvhexmcsbenchmark11.la

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

libdlvhexmcsbenchmark5_la_SOURCES = ./benchmark5/BenchContext5.cpp
libdlvhexmcsbenchmark5_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/ACC_ContextAtom.lo

libdlvhexmcsbenchmark6_la_SOURCES = ./benchmark6/BenchContext6.cpp
libdlvhexmcsbenchmark6_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/ACC_ContextAtom.lo

libdlvhexmcsbenchmark7_la_SOURCES = ./benchmark7/BenchContext7.cpp
libdlvhexmcsbenchmark7_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/ACC_ContextAtom.lo

libdlvhexmcsbenchmark8_la_SOURCES = ./benchmark8/BenchContext8.cpp
libdlvhexmcsbenchmark8_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/ACC_ContextAtom.lo

libdlvhexmcsbenchmark9_la_SOURCES = ./benchmark9/BenchContext9.cpp
libdlvhexmcsbenchmark9_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/ACC_ContextAtom.lo

libdlvhexmcsbenchmark10_la_SOURCES = ./benchmark10/BenchContext10.cpp
libdlvhexmcsbenchmark10_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/ACC_ContextAtom.lo

libdlvhexmcsbenchmark11_la_SOURCES = ./benchmark11/BenchContext11.cpp
libdlvhexmcsbenchmark11_la_LDFLAGS = -avoid-version -module \
 			     $(top_builddir)/src/ACC_ContextAtom.lo
