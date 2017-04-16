AC_PREREQ([2.61])
AC_INIT([dlvhex2-mcsieplugin],[2.0.0],[dlvhex-devel@lists.sourceforge.net])
AC_CONFIG_SRCDIR([src/MCSIEPlugin.cpp])
AC_CONFIG_HEADERS([src/config.h])

AC_CONFIG_MACRO_DIR([m4])
# for documentation of the versioning scheme see
# https://sourceforge.net/apps/trac/dlvhex/wiki/LibraryVersions
DLVHEX_DEFINE_VERSION([MCSIEPLUGIN],[$PACKAGE_VERSION])
DLVHEX_DEFINE_VERSION([DLVHEX_ABI],[7.1.0])

AM_INIT_AUTOMAKE

AC_CANONICAL_HOST

# by default we look into /opt/local and /sw for include files (macports vs. fink)
case $host_os in
     darwin*|macosx*)
        CPPFLAGS="$CPPFLAGS -I/opt/local/include -I/sw/include"
     ;;
esac


# Checks for programs.
AC_PROG_CXX
AC_LANG([C++])

# Checks for header files.
AC_HEADER_DIRENT
AC_CHECK_HEADERS([sys/param.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_LIBTOOL_DLOPEN # we build a module library
AC_DISABLE_STATIC # we don't need a static library
AC_PROG_LIBTOOL

#
# check for other libraries here
#

# check for dlvhex, sets various variables
DLVHEX_REQUIRE([2.0.0])

# where the plugin will be installed by default.
# running configure will take sysplugindir from dlvhex.pc,
# running configure --enable-userinstall will take homeplugindir.
AC_ARG_ENABLE(userinstall, 
             [  --enable-userinstall    Install plugin into home directory],
             [plugindir=$HOME/$DLVHEX_USERPLUGINDIR],
             [plugindir=$DLVHEX_SYSPLUGINDIR]
             )
AC_SUBST([plugindir])
if test "x$plugindir" == "x"; then
	AC_MSG_ERROR([Cannot determine nonempty value for plugindir!])
fi

# checking for boost libs
BOOST_REQUIRE([1.43.0])
BOOST_SMART_PTR
BOOST_STRING_ALGO
BOOST_TOKENIZER

AC_DEFINE([POSIX], [1], [Defined on POSIX systems.])

SAVE_CPPFLAGS="$CPPFLAGS"
SAVE_LIBS="$LIBS"
CPPFLAGS="$CPPFLAGS $DLVHEX_CFLAGS -DBOOST_SYSTEM_NO_DEPRECATED"
LIBS="$DLVHEX_LIBS $LIBS" # prepend to LIBS, append to FLAGS
AC_LINK_IFELSE(dnl
  [AC_LANG_SOURCE(dnl
    [[
    #include <dlvhex2/ASPSolver.h>
    int main(int, char**) { dlvhex::ASPSolver::DLVSoftware::Options o; }
    ]])dnl
  ],[],
  [AC_MSG_ERROR([MCSIE requires dlvhex2 to be built with dlv support: please put dlv in your PATH and reconfigure/rebuild/reinstall dlvhex2, then reconfigure MCSIE])]
  )
CPPFLAGS="$SAVE_CPPFLAGS"
LIBS="$SAVE_LIBS"

#
# all needed makefiles
#
AC_CONFIG_FILES([
  Makefile 
  src/Makefile
  include/Makefile
  testsuite/Makefile
  examples/Makefile
])

AC_OUTPUT

dnl output configuration
cat <<EOF
 
$PACKAGE_TARNAME $PACKAGE_VERSION configuration:

 - Compiler settings
 CC: $CC
 CXX: $CXX
 CFLAGS: $CFLAGS
 CPPFLAGS: $CPPFLAGS
 CXXFLAGS: $CXXFLAGS
 LDFLAGS: $LDFLAGS

 - from pkg-config
 DLVHEX_CFLAGS: $DLVHEX_CFLAGS
 DLVHEX_LIBS: $DLVHEX_LIBS
 DLVHEX_BINDIR: $DLVHEX_BINDIR
 
 - Path settings
 prefix: $prefix
 plugindir: $plugindir
EOF
