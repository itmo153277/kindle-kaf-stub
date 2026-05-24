AC_PREREQ([2.71])

AC_INIT([kaf-stub], [1.0], [viktprog@gmail.com])
AC_COPYRIGHT([Copyright (c) 2026  Viktor Ivanov])

AC_CONFIG_AUX_DIR([auxdir])
AM_INIT_AUTOMAKE([-Wall -Werror])
AM_MAINTAINER_MODE
AM_SILENT_RULES(yes)

AC_CANONICAL_HOST

AC_CONFIG_HEADERS([config.h])

AC_PROG_CC
AC_LANG([C])

AC_ARG_WITH([lipc], AS_HELP_STRING([--with-lipc], [With [open]lipc]), [], [with_lipc=yes])

LIPC_LDFLAGS=""
LIPC_CFLAGS=""
if test "x$with_lipc" = "xno" ; then
    AC_MSG_ERROR([cannot build without lipc])
fi
if test "x$with_lipc" != "xyes" ; then
    LIPC_LDFLAGS="-L$with_lipc/lib"
    LIPC_CFLAGS="-I$with_lipc/include"
fi
with_lipc=no
LIBS_SAVE=$LIBS
CFLAGS_SAVE=$CFLAGS
LIBS="$LIBS $LIPC_LDFLAGS -llipc"
CFLAGS="$CFLAGS $LIPC_CFLAGS"
AC_MSG_CHECKING([whether lipc works])
AC_LINK_IFELSE([AC_LANG_PROGRAM([[@%:@include <openlipc.h>]], [[LipcOpenNoName()]])], [with_lipc=yes])
LIBS=$LIBS_SAVE
CFLAGS=$PFLAGS_SAVE
AC_MSG_RESULT([$with_lipc])
if test "x$with_lipc" = "xno" ; then
    AC_MSG_ERROR([cannot build without lipc])
fi

AC_SUBST(LIPC_LDFLAGS)
AC_SUBST(LIPC_CFLAGS)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
