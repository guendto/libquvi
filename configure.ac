#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])

m4_include([m4/version.m4])

AC_INIT([libquvi], [libquvi_lt_rel], [http://sourceforge.net/apps/trac/quvi/],
        [], [http://quvi.sourceforge.net/])

# Interface:
LT_REL=libquvi_lt_rel
LT_CUR=libquvi_lt_cur
LT_REV=libquvi_lt_rev
LT_AGE=libquvi_lt_age
AC_SUBST([LT_REL])
AC_SUBST([LT_CUR])
AC_SUBST([LT_REV])
AC_SUBST([LT_AGE])

AC_CONFIG_SRCDIR([src/api/new.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([config.aux])
AC_CONFIG_MACRO_DIR([m4])

AC_CANONICAL_SYSTEM
AC_GNU_SOURCE

AC_DEFINE_UNQUOTED([CANONICAL_TARGET], "$target", [...])
AC_DEFINE_UNQUOTED([CANONICAL_HOST], "$host", [...])

AM_INIT_AUTOMAKE([-Wall -Werror foreign dist-bzip2 dist-xz])
AM_SILENT_RULES([yes])

LT_INIT()
LT_PREREQ([2.2])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES([liblua], [lua >= 5.1], [], [
  PKG_CHECK_MODULES([liblua], [lua51 >= 5.1], [], [
    PKG_CHECK_MODULES([liblua], [lua5.1 >= 5.1], [], [
      PKG_CHECK_MODULES(liblua, [lua-5.1 >= 5.1])])
  ])
])
PKG_CHECK_MODULES([libcurl], [libcurl >= 7.18.2])
PKG_CHECK_MODULES([glib], [glib-2.0 >= 2.24])

# Checks for scripts.
PKG_CHECK_MODULES([libquvi_scripts], [libquvi-scripts >= 0.4.0])

scriptsdir=`$PKG_CONFIG --variable scriptsdir libquvi-scripts 2>/dev/null`
versionfile=`$PKG_CONFIG --variable versionfile libquvi-scripts 2>/dev/null`
scriptsmodver=`$PKG_CONFIG --modversion libquvi-scripts 2>/dev/null`

AS_IF([test -z "$scriptsdir"], [
  AC_MSG_ERROR([libquvi-scripts.pc: scriptsdir: variable not found])])

AS_IF([test -z "$versionfile"], [
  AC_MSG_ERROR([libquvi-scripts.pc: versionfile: variable not found])])

AC_DEFINE_UNQUOTED([SCRIPTSDIR], ["$scriptsdir"], [We have scriptsdir])
AC_DEFINE_UNQUOTED([VERSIONFILE], ["$versionfile"], [We have versionfile])

# Checks for header files.
AC_CHECK_HEADERS(
  [memory.h stdarg.h stddef.h stdint.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_TYPES([ptrdiff_t])
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([getcwd memset strdup strerror strrchr strstr])
AC_FUNC_REALLOC
AC_FUNC_MALLOC

# Version.
VN=`$srcdir/gen-ver.sh $srcdir`
AC_DEFINE_UNQUOTED([VN], ["$VN"], [We have version number from gen-ver.sh])

# --with-examples
AC_ARG_WITH([examples],
  [AS_HELP_STRING([--with-examples],
    [build examples @<:@default=no@:>@])],
  [],
  [with_examples=no])
AM_CONDITIONAL([WITH_EXAMPLES], [test x"$with_examples" != "xno"])

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
  doc/Makefile
  examples/Makefile
  src/misc/Makefile
  src/curl/Makefile
  src/net/Makefile
  src/api/Makefile
  src/lua/Makefile
  src/quvi-1.0/quvi/Makefile
  src/quvi-1.0/Makefile
  src/Makefile
  libquvi-1.0.pc])
AC_OUTPUT

AC_MSG_NOTICE([
  version:        ${VERSION} (${VN})
  host setup:     ${host}
  prefix:         ${prefix}
  cflags:         ${CFLAGS}
  compiler:       ${CC}
libquvi-scripts.pc:
  modversion:     ${scriptsmodver}
  scriptsdir:     ${scriptsdir}
  versionfile:    ${versionfile}
Options:
  build libquvi:  shared=${enable_shared} static=${enable_static}
  build examples: ${with_examples}
  install manual: ${with_manual}])
