PHP_INCLUDE = `php-config --includes`
PHP_LIBS = `php-config --libs`
PHP_LDFLAGS = `php-config --ldflags`
PHP_INCLUDE_DIR = `php-config --include-dir`
PHP_EXTENSION_DIR = `php-config --extension-dir`

args_test.so: args_test.cpp
	c++ -DHAVE_CONFIG_H -g -o args_test.so -O0 -fPIC -shared args_test.cpp -std=c++11 -lphpx ${PHP_INCLUDE} -I${PHP_INCLUDE_DIR} ${PHP_LIBS} ${PHP_LDFLAGS}
install: args_test.so
	cp args_test.so ${PHP_EXTENSION_DIR}/
clean:
	rm *.so
