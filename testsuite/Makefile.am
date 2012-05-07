EXTRA_DIST = run-dlvhex-tests.sh diagexpl_comp.py


TESTS_ENVIRONMENT = \
  TOP_SRCDIR=$(top_srcdir) \
  DLVHEX="$(DLVHEX_BINDIR)/dlvhex2 -s --plugindir=!:$(top_builddir)/src:$(top_builddir)/examples --iepath=$(top_srcdir)/examples/ --solver=genuinegc --flpcheck=ufs" \
  TESTS="$(top_srcdir)/examples/diagrewriting.test $(top_srcdir)/examples/eqrewriting.test $(top_srcdir)/examples/explrewriting.test" \
  EXAMPLESDIR=$(top_srcdir)/examples \
  OUTDIR=$(top_srcdir)/examples/
  
TESTS = $(top_srcdir)/testsuite/run-dlvhex-tests.sh

