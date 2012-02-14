lib_LTLIBRARIES = libdlvhex-mcsie.la
plugin_LTLIBRARIES = libdlvhexplugin-mcsie.la 

# most parts of the implementation are in here
# this is not a plugin library but a regular shared library with a version
#
# the reason for that is, that additional context semantics can be implemented
# in additional plugins which then depend on libdlvhex-mcsie
# see the testcases for examples of such additional plugins
libdlvhex_mcsie_la_SOURCES = \
  ACC_ContextAtom.cpp \
  BaseContextPlugin.cpp \
  BaseContextAtom.cpp \
  BridgeRule.cpp \
  BridgeRuleEntry.cpp \
  Context.cpp \
  DLV_ASP_ContextAtom.cpp \
	EquilibriumPrinter.cpp \
  InputConverterDiagnoses.cpp \
  InputConverterExplanations.cpp \
  InputConverterOPEquilibria.cpp \
  InputParser.cpp \
  MCS.cpp \
	MinPrintDualConvertFinalCallback.cpp \
  MinimalNotionCollector.cpp \
  NotionPrinter.cpp \
	PrintAndAccumulateModelCallback.cpp \
  ProgramCtxData.cpp \
  SaturationMetaAtom.cpp

nopfoo = \
  OutputRewriter.cpp \
  Timing.cpp

# for more information on `-version-info' see
# <http://www.gnu.org/software/libtool/manual.html#Versioning>, and
# the USENIX paper `Library Interface Versioning in Solaris and Linux'
# <http://www.usenix.org/publications/library/proceedings/als00/2000papers/papers/full_papers/browndavid/browndavid.pdf>
libdlvhex_mcsie_la_LDFLAGS = -version-info 2:0:0

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
  $(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

# the plugin library module, which links against libdlvhex-mcsie
libdlvhexplugin_mcsie_la_SOURCES = MCSIEPlugin.cpp
libdlvhexplugin_mcsie_la_LDFLAGS = -avoid-version -module
libdlvhexplugin_mcsie_la_LIBADD = libdlvhex-mcsie.la
