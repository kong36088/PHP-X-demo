<?php
var_dump(cpp_ext_test([], 42.33, "jjj",111));
var_dump(cpp_ext_test2(["abc", "456"], false));
var_dump(myClass::test());

$o = new myClass;
$o->pset();
var_dump($o->pget());
var_dump($o);
var_dump(myClass::class);
var_dump($o->getClassName()); //与myClass::class相同作用
var_dump($o->argTest([]));
var_dump(json_encode([1,2,3],1,1,1,1,1,1,1,1,1));
ReflectionFunction::export("cpp_ext_test");