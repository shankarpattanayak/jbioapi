#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_INIT([[JBioAPI]],[[0.1.0]],[[michael@qrivy.net]],[[jbioapi]])
AC_PREREQ(2.59)
AC_CANONICAL_BUILD
AC_CANONICAL_TARGET

AC_CONFIG_SRCDIR(src/jbioapi_wrap.c)
dnl Every other copy of the package version number gets its value from here
AM_INIT_AUTOMAKE([foreign dist-bzip2 no-installinfo no-installman tar-pax])

AC_SUBST(VERSION)

ISODATE=`date +%Y-%m-%d`
AC_SUBST(ISODATE)


dnl Checks for programs.
AC_PROG_INSTALL
AC_PROG_CC
AC_DISABLE_STATIC
AC_PROG_LIBTOOL
AC_PROG_RANLIB 
AC_PROG_JAVAC
AC_JNI_INCLUDE_DIR
for JNI_INCLUDE_DIR in $JNI_INCLUDE_DIRS
do
	CPPFLAGS="$CPPFLAGS -I$JNI_INCLUDE_DIR"
done

dnl we don't use this, yet
dnl AC_PROG_SWIG(1.3.24)

# Checks for libraries.
AC_CHECK_LIB([bioapi100], [BioAPI_Init])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADER([limits.h], ,AC_MSG_ERROR([cannot find required header: limits.h]))

AC_DEFINE(UNIX)

AC_CHECK_HEADER([bioapi.h], ,AC_MSG_ERROR([cannot find required header: bioapi.h]))
AC_CHECK_HEADER([bioapi_util.h], ,AC_MSG_ERROR([cannot find required header: bioapi_util.h]))

#The "#include" is a workaround until bioapi_uuid.h is fixed
AC_CHECK_HEADER([bioapi_uuid.h], ,AC_MSG_ERROR([cannot find required header: bioapi_uuid.h]),[#include <bioapi_type.h>])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memmove memset])

AC_CONFIG_FILES([Makefile src/Makefile])

AC_OUTPUT
