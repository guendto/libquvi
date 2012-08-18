#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])

m4_include([m4/version.m4])

AC_INIT([libquvi], m4_esyscmd([./gen-ver.sh -c | tr -d '\n']),
        [http://quvi.sf.net/bugs/],[],[http://quvi.sf.net/])

# Interface
LT_CUR=libquvi_lt_cur
LT_REV=libquvi_lt_rev
LT_AGE=libquvi_lt_age
AC_SUBST([LT_CUR])
AC_SUBST([LT_REV])
AC_SUBST([LT_AGE])

AC_CONFIG_SRCDIR([src/api/new.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([config.aux])
AC_CONFIG_MACRO_DIR([m4])

AC_CANONICAL_TARGET
AC_USE_SYSTEM_EXTENSIONS

AC_DEFINE_UNQUOTED([CANONICAL_TARGET], "$target", [...])
AC_DEFINE_UNQUOTED([CANONICAL_BUILD], "$build", [...])
AC_DEFINE_UNQUOTED([CANONICAL_HOST], "$host", [...])

AM_INIT_AUTOMAKE([1.11.1 -Wall -Werror dist-xz no-dist-gzip tar-ustar])
AM_SILENT_RULES([yes])
#AM_PROG_AR

LT_INIT([disable-static])
LT_PREREQ([2.2.6])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O

AC_PATH_PROG([DOXYGEN], [doxygen], [no])
AM_CONDITIONAL([HAVE_DOXYGEN], [test x"$DOXYGEN" != "xno"])
AC_SUBST([DOXYGEN])

AC_PATH_PROG([DATE], [date], [no])
AS_IF([test "$DATE" != x"$xno"], [build_time=`$DATE +"%F %T %z"`])
AC_DEFINE_UNQUOTED([BUILD_TIME], ["$build_time"], [We have build time])

AC_PATH_PROG([VALGRIND], [valgrind], [no])
AM_CONDITIONAL([HAVE_VALGRIND], [test x"$VALGRIND" != "xno"])
AC_SUBST([VALGRIND])

# Checks for libraries.
PKG_CHECK_MODULES([liblua], [lua >= 5.1], [], [
  PKG_CHECK_MODULES([liblua], [lua51 >= 5.1], [], [
    PKG_CHECK_MODULES([liblua], [lua5.1 >= 5.1], [], [
      PKG_CHECK_MODULES(liblua, [lua-5.1 >= 5.1])])
  ])
])
PKG_CHECK_MODULES([libproxy], [libproxy-1.0 >= 0.3.1])
PKG_CHECK_MODULES([libcurl], [libcurl >= 7.21])
PKG_CHECK_MODULES([glib], [glib-2.0 >= 2.24])

# Checks for scripts.
pkg_scripts=libquvi-scripts-0.9

AC_ARG_WITH([scriptsdir],
  [AS_HELP_STRING([--with-scriptsdir=DIR],
    [Set libquvi-scripts directory to DIR. This negates the
    libquvi-scripts check.  DIR is assumed to contain the files
    installed with libquvi-scripts to the
      $prefix/share/libquvi-scripts/ directory.])],
  [scriptsdir=$withval
   versionfile=$scriptsdir/version],
  [PKG_CHECK_MODULES([libquvi_scripts], ["$pkg_scripts" >= 0.9])
    scriptsdir=`$PKG_CONFIG --variable scriptsdir $pkg_scripts 2>/dev/null`
    versionfile=`$PKG_CONFIG --variable versionfile $pkg_scripts 2>/dev/null`
    scriptsmodver=`$PKG_CONFIG --modversion $pkg_scripts 2>/dev/null`])

AS_IF([test -z "$scriptsdir"], [
  AC_MSG_ERROR([scriptsdir: variable not found])])

AS_IF([ ! test -d "$scriptsdir"], [
  AC_MSG_ERROR([$scriptsdir: does not exist or is not a directory])])

AS_IF([test -z "$versionfile"], [
  AC_MSG_ERROR([versionfile: variable not found])])

AS_IF([ ! test -f "$versionfile"], [
  AC_MSG_WARN([$versionfile: does not exist or is not not a regular file])])

AC_DEFINE_UNQUOTED([SCRIPTSDIR], ["$scriptsdir"], [We have scriptsdir])
AC_DEFINE_UNQUOTED([VERSIONFILE], ["$versionfile"], [We have versionfile])

scriptsver=`head -n1 "$versionfile" 2>/dev/null`

# Checks for header files.
AC_CHECK_HEADERS([stdint.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([strrchr])

# Version.
VN=`$srcdir/gen-ver.sh`
AC_DEFINE_UNQUOTED([VN], ["$VN"], [We have version number from gen-ver.sh])

VN_C=`$srcdir/gen-ver.sh -c`
AC_SUBST([VN_C])

# Version: Major/Minor -pair, used to find the libquvi scripts.
# e.g. $prefix/share/libquvi-scripts/$maj.$min/
VERSION_MM=`$srcdir/gen-ver.sh -c -m`
AC_DEFINE_UNQUOTED([VERSION_MM], "$VERSION_MM", [Version major/minor])

# --with-manual
AC_ARG_WITH([manual],
  [AS_HELP_STRING([--with-manual],
    [install manual pages @<:@default=yes@:>@])],
  [],
  [with_manual=yes])
AM_CONDITIONAL([WITH_MANUAL], [test x"$with_manual" != "xno"])

AC_CONFIG_FILES([
  Makefile
  doc/man3/Makefile
  doc/dox/Makefile
  doc/dox/Doxyfile
  doc/Makefile
  examples/Makefile
  examples/lib/Makefile
  src/misc/Makefile
  src/curl/Makefile
  src/net/Makefile
  src/api/Makefile
  src/lua/Makefile
  src/quvi-0.9/quvi/Makefile
  src/quvi-0.9/Makefile
  src/Makefile
  tests/Makefile
  tests/lib/Makefile
  libquvi-0.9.pc])
AC_OUTPUT

AC_MSG_NOTICE([
  version         ${VERSION}
  prefix          ${prefix}
  compiler        ${CC}
  cflags          ${CFLAGS}
System types
  target          ${target}
  build           ${build}
  host            ${host}
Options
  install manual  ${with_manual}
libquvi-scripts
  .pc modversion  ${scriptsmodver}
  versionfile     ${versionfile}
    version       ${scriptsver}
  scriptsdir      ${scriptsdir}])
