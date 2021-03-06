<?php
ReflectionClass::export("ArgsTest");

$at = new ArgsTest();

$at->noneArgs();  //正确
$at->noneArgs(1,2,3,4);  //为了向下兼容，没有定义参数的不会报错

$at->oneArgs("abb");  //正确
$at->oneArgs("sta",123); //报Warning，参数过多

$at->twoArgs();   //报Warning，参数缺失
$at->twoArgs("abb",456);  //正确
$at->twoArgs(1,2,3); //报Warning，参数过多

$at->threeArgs();  //报Warning，参数缺失
$at->threeArgs(1,2,3);  //正确

fnTest1();  //正确
fnTest1(1,2,3,4);  //为了向下兼容，没有定义参数的不会报错

fnTest2();  //报Warning，参数缺失
fnTest2(1); //正确
fnTest2(1,"string"); //正确
fnTest2(1,"string",123.11); //报Warning，参数过多

/* 输出结果
Class [ <internal:args_test> class ArgsTest ] {

  - Constants [0] {
  }

  - Static properties [0] {
  }

  - Static methods [0] {
  }

  - Properties [0] {
  }

  - Methods [4] {
    Method [ <internal:args_test> public method noneArgs ] {

      - Parameters [0] {
      }
    }

    Method [ <internal:args_test> public method oneArgs ] {

      - Parameters [1] {
        Parameter #0 [ <required> $para1 ]
      }
    }

    Method [ <internal:args_test> public method twoArgs ] {

      - Parameters [2] {
        Parameter #0 [ <required> $para1 ]
        Parameter #1 [ <required> $para2 ]
      }
    }

    Method [ <internal:args_test> public method threeArgs ] {

      - Parameters [3] {
        Parameter #0 [ <required> $para1 ]
        Parameter #1 [ <required> $para2 ]
        Parameter #2 [ <optional> $para3 ]
      }
    }
  }
}

Args: 
ArgsTest::noneArgs() called
Args: 1 2 3 4 
ArgsTest::noneArgs() called
Args: abb 
ArgsTest::oneArgs() called
PHP Warning:  ArgsTest::oneArgs() expects exactly 1 parameter, 2 given in /share/docker/c/www/PHP-X-demo/args/tests/main.php on line 10

Warning: ArgsTest::oneArgs() expects exactly 1 parameter, 2 given in /share/docker/c/www/PHP-X-demo/args/tests/main.php on line 10
PHP Warning:  ArgsTest::twoArgs() expects exactly 2 parameters, 0 given in /share/docker/c/www/PHP-X-demo/args/tests/main.php on line 12

Warning: ArgsTest::twoArgs() expects exactly 2 parameters, 0 given in /share/docker/c/www/PHP-X-demo/args/tests/main.php on line 12
Args: abb 456 
ArgsTest::twoArgs() called
PHP Warning:  ArgsTest::twoArgs() expects exactly 2 parameters, 3 given in /share/docker/c/www/PHP-X-demo/args/tests/main.php on line 14

Warning: ArgsTest::twoArgs() expects exactly 2 parameters, 3 given in /share/docker/c/www/PHP-X-demo/args/tests/main.php on line 14
PHP Warning:  ArgsTest::threeArgs() expects at least 2 parameters, 0 given in /share/docker/c/www/PHP-X-demo/args/tests/main.php on line 16

Warning: ArgsTest::threeArgs() expects at least 2 parameters, 0 given in /share/docker/c/www/PHP-X-demo/args/tests/main.php on line 16
Args: 1 2 3 
ArgsTest::threeArgs() called
Args: 
fnTest1() called
Args: 1 2 3 4 
fnTest1() called
PHP Warning:  fnTest2() expects at least 1 parameter, 0 given in /share/docker/c/www/PHP-X-demo/args/tests/main.php on line 22

Warning: fnTest2() expects at least 1 parameter, 0 given in /share/docker/c/www/PHP-X-demo/args/tests/main.php on line 22
Args: 1 
fnTest2() called
Args: 1 string 
fnTest2() called
PHP Warning:  fnTest2() expects at most 2 parameters, 3 given in /share/docker/c/www/PHP-X-demo/args/tests/main.php on line 25

Warning: fnTest2() expects at most 2 parameters, 3 given in /share/docker/c/www/PHP-X-demo/args/tests/main.php on line 25
*/
