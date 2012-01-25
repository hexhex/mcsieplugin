lib_LTLIBRARIES = libldlvhexmcsdiagexpl.la
plugin_LTLIBRARIES = libdlvhexmcsdiagexpl.la 

# most parts of the implementation are in here
# this is not a plugin library but a regular shared library with a version
#
# the reason for that is, that additional context semantics can be implemented
# in additional plugins which then depend on libldlvhexmcsdiagexpl
# see the testcases for examples of such additional plugins
libldlvhexmcsdiagexpl_la_SOURCES = \
  ProgramCtxData.cpp \
  BaseContextPlugin.cpp \
  DLV_ASP_ContextAtom.cpp \
  InputConverter.cpp \
  SaturationMetaAtom.cpp

nopfoo = \
  InputConverterHelper.cpp \
  InputConverterDiagnosis.cpp \
  InputConverterExplanations.cpp \
  BridgeRule.cpp \
  BridgeRuleEntry.cpp \
  ParseContext.cpp \
  ACC_ContextAtom.cpp \
  OutputRewriter.cpp \
  EquilibriumPrintVisitor.cpp \
  DiagExplPrintVisitor.cpp \
  ExplanationPrintVisitor.cpp \
  Timing.cpp

# for more information on `-version-info' see
# <http://www.gnu.org/software/libtool/manual.html#Versioning>, and
# the USENIX paper `Library Interface Versioning in Solaris and Linux'
# <http://www.usenix.org/publications/library/proceedings/als00/2000papers/papers/full_papers/browndavid/browndavid.pdf>
libldlvhexmcsdiagexpl_la_LDFLAGS = -version-info 2:0:0

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
  $(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

# the plugin library module, which links against libldlvhexmcsdiagexpl
libdlvhexmcsdiagexpl_la_SOURCES = MCSIEPlugin.cpp
libdlvhexmcsdiagexpl_la_LDFLAGS = -avoid-version -module
libdlvhexmcsdiagexpl_la_LIBADD = libldlvhexmcsdiagexpl.la
