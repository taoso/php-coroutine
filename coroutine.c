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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_coroutine.h"

ZEND_DECLARE_MODULE_GLOBALS(coroutine)

/* True global resources - no need for thread safety here */
static int le_coroutine;

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("coroutine.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_coroutine_globals, coroutine_globals)
    STD_PHP_INI_ENTRY("coroutine.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_coroutine_globals, coroutine_globals)
PHP_INI_END()
/* }}} */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_coroutine_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_coroutine_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "coroutine", arg);

	RETURN_STR(strg);
}
/* }}} */

/* {{{ php_coroutine_init_globals
 */
static void php_coroutine_init_globals(zend_coroutine_globals *coroutine_globals)
{
	coroutine_globals->global_value = 0;
	coroutine_globals->global_string = NULL;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(coroutine)
{
	REGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(coroutine)
{
	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(coroutine)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "coroutine support", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ coroutine_functions[]
 *
 * Every user visible function must have an entry in coroutine_functions[].
 */
const zend_function_entry coroutine_functions[] = {
	PHP_FE(confirm_coroutine_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in coroutine_functions[] */
};
/* }}} */

/* {{{ coroutine_module_entry
 */
zend_module_entry coroutine_module_entry = {
	STANDARD_MODULE_HEADER,
	"coroutine",
	coroutine_functions,
	PHP_MINIT(coroutine),
	PHP_MSHUTDOWN(coroutine),
	NULL,
	NULL,
	PHP_MINFO(coroutine),
	PHP_COROUTINE_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_COROUTINE
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(coroutine)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
