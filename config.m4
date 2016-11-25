dnl $Id$
dnl config.m4 for extension mio_logger

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(mio_logger, for mio_logger support,
dnl Make sure that the comment is aligned:
dnl [  --with-mio_logger             Include mio_logger support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(mio_logger, whether to enable mio_logger support,
dnl Make sure that the comment is aligned:
dnl [  --enable-mio_logger           Enable mio_logger support])

if test "$PHP_MIO_LOGGER" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-mio_logger -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/mio_logger.h"  # you most likely want to change this
  dnl if test -r $PHP_MIO_LOGGER/$SEARCH_FOR; then # path given as parameter
  dnl   MIO_LOGGER_DIR=$PHP_MIO_LOGGER
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for mio_logger files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       MIO_LOGGER_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$MIO_LOGGER_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the mio_logger distribution])
  dnl fi

  dnl # --with-mio_logger -> add include path
  dnl PHP_ADD_INCLUDE($MIO_LOGGER_DIR/include)

  dnl # --with-mio_logger -> check for lib and symbol presence
  dnl LIBNAME=mio_logger # you may want to change this
  dnl LIBSYMBOL=mio_logger # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MIO_LOGGER_DIR/$PHP_LIBDIR, MIO_LOGGER_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_MIO_LOGGERLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong mio_logger lib version or lib not found])
  dnl ],[
  dnl   -L$MIO_LOGGER_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(MIO_LOGGER_SHARED_LIBADD)

  PHP_NEW_EXTENSION(mio_logger, mio_logger.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
