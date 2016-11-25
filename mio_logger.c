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
  | Author: renshan <1005110700@qq.com>		                         |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_mio_logger.h"
#include "mio_logger_funcs.h"

/* If you declare any globals in php_mio_logger.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(mio_logger)
*/

/* True global resources - no need for thread safety here */
static int ce_mio_logger;

zend_class_entry *mio_logger_ce;


/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("mio_logger.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_mio_logger_globals, mio_logger_globals)
    STD_PHP_INI_ENTRY("mio_logger.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_mio_logger_globals, mio_logger_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ Construct of MioLogger */
ZEND_METHOD(mio_logger, __construct)
{
	char *channel,
		 *path;

	size_t c_len,
		   p_len;


	/** | means parameters after are optional **/
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "|ss", &channel, &c_len, &path, &p_len) == FAILURE) {
		return;
	}

	/* Set path, if get channel from __construct */
	if (strlen(channel) > 1) {
		zend_update_property_string(mio_logger_ce, getThis(), "channel", 7, channel TSRMLS_CC);
	}

	/* Set path, if get path from __construct  */
	if (strlen(path) > 1) {
		zend_update_property_string(mio_logger_ce, getThis(), "path", 4, path TSRMLS_CC);
	}

}
/* }}} */


/* {{{ setPath of MioLogger */
ZEND_METHOD(mio_logger, setPath)
{
	char *path;
	size_t p_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &path, &p_len) == FAILURE) {
		return;
	}

	if (strlen(path) > 1) {
		zend_update_property_stringl(mio_logger_ce, getThis(), "path", 4, path, strlen(path));
	}
}
/* }}} */

/* {{{ getPath of MioLogger */
ZEND_METHOD(mio_logger, getPath)
{

	zval *rv;
	zval *path = zend_read_property(mio_logger_ce, getThis(), "path", 4, 1, rv);

	RETURN_STR(strpprintf(0, "%s", path->value.str->val));
}
/* }}} */

/* {{{ getChannel of MioLogger */
ZEND_METHOD(mio_logger, setChannel)
{
	char *channel;
	size_t c_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &channel, &c_len) == FAILURE) {
		return;
	}

	if (strlen(channel) > 1) {
		zend_update_property_stringl(mio_logger_ce, getThis(), "channel", 7, channel, strlen(channel));
	}
}
/* }}} */

/* {{{ getChannel of MioLogger */
ZEND_METHOD(mio_logger, getChannel)
{

	zval *rv;
	zval *channel = zend_read_property(mio_logger_ce, getThis(), "channel", 7, 1, rv);

	RETURN_STR(strpprintf(0, "%s", channel->value.str->val));
}
/* }}} */

/*{{{ Method emergency */
ZEND_METHOD(mio_logger, emergency)
{
	char *log_content;
	size_t len;
	zval *rv;
	zval *path;
	zval *channel;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &log_content, &len) == FAILURE) {
		return;
	}

	path = zend_read_property(mio_logger_ce, getThis(), "path", 4, 1, rv);
	channel = zend_read_property(mio_logger_ce, getThis(), "channel", 7, 1, rv);

	int ret = write_log(path->value.str->val, channel->value.str->val, MIO_EMERGENCY, log_content);

	RETURN_LONG(ret);

}
/* }}} */

/*{{{ Method alert */
ZEND_METHOD(mio_logger, alert)
{
	char *log_content;
	size_t len;
	zval *rv;
	zval *path;
	zval *channel;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &log_content, &len) == FAILURE) {
		return;
	}

	path = zend_read_property(mio_logger_ce, getThis(), "path", 4, 1, rv);
	channel = zend_read_property(mio_logger_ce, getThis(), "channel", 7, 1, rv);

	int ret = write_log(path->value.str->val, channel->value.str->val, MIO_ALERT, log_content);

	RETURN_LONG(ret);

}
/* }}} */

/*{{{ Method emergency */
ZEND_METHOD(mio_logger, critical)
{
	char *log_content;
	size_t len;
	zval *rv;
	zval *path;
	zval *channel;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &log_content, &len) == FAILURE) {
		return;
	}

	path = zend_read_property(mio_logger_ce, getThis(), "path", 4, 1, rv);
	channel = zend_read_property(mio_logger_ce, getThis(), "channel", 7, 1, rv);

	int ret = write_log(path->value.str->val, channel->value.str->val, MIO_CRITICAL, log_content);

	RETURN_LONG(ret);

}
/* }}} */

/*{{{ Method error */
ZEND_METHOD(mio_logger, error)
{
	char *log_content;
	size_t len;
	zval *rv;
	zval *path;
	zval *channel;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &log_content, &len) == FAILURE) {
		return;
	}

	path = zend_read_property(mio_logger_ce, getThis(), "path", 4, 1, rv);
	channel = zend_read_property(mio_logger_ce, getThis(), "channel", 7, 1, rv);

	int ret = write_log(path->value.str->val, channel->value.str->val, MIO_ERROR, log_content);

	RETURN_LONG(ret);

}
/* }}} */

/*{{{ Method warning */
ZEND_METHOD(mio_logger, warning)
{
	char *log_content;
	size_t len;
	zval *rv;
	zval *path;
	zval *channel;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &log_content, &len) == FAILURE) {
		return;
	}

	path = zend_read_property(mio_logger_ce, getThis(), "path", 4, 1, rv);
	channel = zend_read_property(mio_logger_ce, getThis(), "channel", 7, 1, rv);

	int ret = write_log(path->value.str->val, channel->value.str->val, MIO_WARNING, log_content);

	RETURN_LONG(ret);

}
/* }}} */

/*{{{ Method info */
ZEND_METHOD(mio_logger, info)
{
	char *log_content;
	size_t len;
	zval *rv;
	zval *path;
	zval *channel;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &log_content, &len) == FAILURE) {
		return;
	}

	path = zend_read_property(mio_logger_ce, getThis(), "path", 4, 1, rv);
	channel = zend_read_property(mio_logger_ce, getThis(), "channel", 7, 1, rv);

	int ret = write_log(path->value.str->val, channel->value.str->val, MIO_INFO, log_content);

	RETURN_LONG(ret);

}
/* }}} */

/*{{{ Method debug */
ZEND_METHOD(mio_logger, debug)
{
	char *log_content;
	size_t len;
	zval *rv;
	zval *path;
	zval *channel;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &log_content, &len) == FAILURE) {
		return;
	}

	path = zend_read_property(mio_logger_ce, getThis(), "path", 4, 1, rv);
	channel = zend_read_property(mio_logger_ce, getThis(), "channel", 7, 1, rv);

	int ret = write_log(path->value.str->val, channel->value.str->val, MIO_DEBUG, log_content);

	RETURN_LONG(ret);

}
/* }}} */

/* {{{ php_mio_logger_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_mio_logger_init_globals(zend_mio_logger_globals *mio_logger_globals)
{
	mio_logger_globals->global_value = 0;
	mio_logger_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ mio_logger_functions[]
 *
 * Every user visible function must have an entry in mio_logger_functions[].
 */
const zend_function_entry mio_logger_functions[] = {
	//PHP_FE(confirm_mio_logger_compiled,	NULL)		/* For testing, remove later. */
	//PHP_FE(mio_log,	NULL)		/* For testing, remove later. */
	//PHP_FE_END	/* Must be the last line in mio_logger_functions[] */
	
	ZEND_ME(mio_logger, __construct, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(mio_logger, setChannel, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(mio_logger, getChannel, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(mio_logger, setPath, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(mio_logger, getPath, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(mio_logger, emergency, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(mio_logger, alert, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(mio_logger, critical, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(mio_logger, error, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(mio_logger, warning, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(mio_logger, info, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(mio_logger, debug, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END	/* Must be the last line in mio_logger_functions[] */
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(mio_logger)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/

	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "MioLogger", mio_logger_functions);
	mio_logger_ce = zend_register_internal_class(&ce TSRMLS_CC);

	/* 
	Define const variable for  MioLogger 
	*/
	/* Level Critical */
	zend_declare_class_constant_stringl(mio_logger_ce, MIO_EMERGENCY, strlen(MIO_EMERGENCY), MIO_EMERGENCY, strlen(MIO_EMERGENCY) TSRMLS_DC);
	/* Level Alert */
	zend_declare_class_constant_stringl(mio_logger_ce, MIO_ALERT, strlen(MIO_ALERT), MIO_ALERT, strlen(MIO_ALERT) TSRMLS_DC);
	/* Level Critical */
	zend_declare_class_constant_stringl(mio_logger_ce, MIO_CRITICAL, strlen(MIO_CRITICAL), MIO_CRITICAL, strlen(MIO_CRITICAL) TSRMLS_DC);
	/* Level Error */
	zend_declare_class_constant_stringl(mio_logger_ce, MIO_ERROR, strlen(MIO_ERROR), MIO_ERROR, strlen(MIO_ERROR) TSRMLS_DC);
	/* Level Warning */
	zend_declare_class_constant_stringl(mio_logger_ce, MIO_WARNING, strlen(MIO_WARNING), MIO_WARNING, strlen(MIO_WARNING) TSRMLS_DC);
	/* Level Info */
	zend_declare_class_constant_stringl(mio_logger_ce, MIO_INFO, strlen(MIO_INFO), MIO_INFO, strlen(MIO_INFO) TSRMLS_DC);
	/* Level Debug */
	zend_declare_class_constant_stringl(mio_logger_ce, MIO_DEBUG, strlen(MIO_DEBUG), MIO_DEBUG, strlen(MIO_DEBUG) TSRMLS_DC);

	
	/*
	Define the path and channel variable
	*/
	zend_declare_property_null(mio_logger_ce, "channel", 7, ZEND_ACC_PRIVATE TSRMLS_DC);
	zend_declare_property_null(mio_logger_ce, "path", 4, ZEND_ACC_PRIVATE TSRMLS_DC);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(mio_logger)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(mio_logger)
{
#if defined(COMPILE_DL_MIO_LOGGER) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(mio_logger)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(mio_logger)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "mio_logger support", "enabled");
	php_info_print_table_row(2, "mio_logger version", "1.0.0");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* {{{ mio_logger_module_entry
 */
zend_module_entry mio_logger_module_entry = {
	STANDARD_MODULE_HEADER,
	"mio_logger",
	mio_logger_functions,
	PHP_MINIT(mio_logger),
	PHP_MSHUTDOWN(mio_logger),
	PHP_RINIT(mio_logger),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(mio_logger),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(mio_logger),
	PHP_MIO_LOGGER_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MIO_LOGGER
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(mio_logger)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
