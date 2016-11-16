dnl $Id$
dnl config.m4 for extension coroutine

PHP_ARG_ENABLE(coroutine, whether to enable coroutine support,
[  --enable-coroutine           Enable coroutine support])

if test "$PHP_COROUTINE" != "no"; then
  PHP_NEW_EXTENSION(coroutine, coroutine.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
