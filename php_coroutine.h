/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_COROUTINE_H
#define PHP_COROUTINE_H

extern zend_module_entry coroutine_module_entry;
#define phpext_coroutine_ptr &coroutine_module_entry

#define PHP_COROUTINE_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_COROUTINE_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_COROUTINE_API __attribute__ ((visibility("default")))
#else
#	define PHP_COROUTINE_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(coroutine)
	zend_long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(coroutine)

#define COROUTINE_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(coroutine, v)

#if defined(ZTS) && defined(COMPILE_DL_COROUTINE)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

extern ZEND_API zend_class_entry *zend_ce_coroutine;
typedef struct _zend_coroutine zend_coroutine;

struct _zend_coroutine {
	int id;
	zval *closure;
	zend_object std;
};

static inline zend_coroutine *zend_coroutine_obj_from_obj(zend_object *obj) {
	return (zend_coroutine*)((char*)(obj) - XtOffsetOf(zend_coroutine, std));
}

#define Z_COROUTINE_P(zv)  zend_coroutine_obj_from_obj(Z_OBJ_P((zv)))

void zend_register_coroutine_ce(void);

#endif	/* PHP_COROUTINE_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
