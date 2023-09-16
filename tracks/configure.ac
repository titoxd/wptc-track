#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([wptc-track],[0.1.3],[titoxd.wikimedia@gmail.com])
AC_CONFIG_SRCDIR([track.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC


# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h strings.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset strcasecmp strerror strstr])

PKG_CHECK_MODULES(TRACK, cairo >= 1.0.0)
AC_SUBST(TRACK_CFLAGS)
AC_SUBST(TRACK_LIBS)

AC_ARG_WITH(tracks-data, AS_HELP_STRING([--with-tracks-data=$DIR],[Change location of tracks data]),
	    tracksdata=$withval, [tracksdata="../data"])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
