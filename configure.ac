AC_PREREQ(2.61)

# main author of original plugin: markus.boegl@student.tuwien.ac.at
AC_INIT([dlvhex-mcsieplugin],[2.0.0],[ps@kr.tuwien.ac.at])

AC_CONFIG_SRCDIR([src/MCSdiagexplPlugin.cpp])

AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_MACRO_DIR([m4])

MAJOR=`echo $PACKAGE_VERSION | sed "s/^\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/"`
MINOR=`echo $PACKAGE_VERSION | sed "s/^\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/"`
MICRO=`echo $PACKAGE_VERSION | sed "s/^\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/"`

AC_DEFINE_UNQUOTED([MCSDIAGEXPLPLUGIN_MAJOR], [$MAJOR], [Major version number of the mcsie-plugin])
AC_DEFINE_UNQUOTED([MCSDIAGEXPLPLUGIN_MINOR], [$MINOR], [Minor version number of the mcsie-plugin])
AC_DEFINE_UNQUOTED([MCSDIAGEXPLPLUGIN_MICRO], [$MICRO], [Micro version number of the mcsie-plugin])


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

#
# of course we need dlvhex itself!
#
PKG_CHECK_MODULES([DLVHEX], [dlvhex >= 2.0])
_PKG_CONFIG([DLVHEX_USERPLUGINDIR], [variable=userplugindir], [dlvhex >= 2.0])
_PKG_CONFIG([DLVHEX_SYSPLUGINDIR], [variable=sysplugindir], [dlvhex >= 2.0])
_PKG_CONFIG([DLVHEX_BINDIR], [variable=bindir], [dlvhex >= 2.0])
DLVHEX_USERPLUGINDIR=$pkg_cv_DLVHEX_USERPLUGINDIR
DLVHEX_SYSPLUGINDIR=$pkg_cv_DLVHEX_SYSPLUGINDIR
DLVHEX_BINDIR=$pkg_cv_DLVHEX_BINDIR
AC_SUBST(DLVHEX_USERPLUGINDIR)
AC_SUBST(DLVHEX_SYSPLUGINDIR)
AC_SUBST(DLVHEX_BINDIR)

SAVE_CPPFLAGS="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS $DLVHEX_CFLAGS"
AC_CHECK_HEADER([dlvhex/OnlineModelBuilder.hpp],,[AC_MSG_ERROR([Cannot find dlvhex headers!])])
CPPFLAGS="$SAFE_CPPFLAGS"

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

