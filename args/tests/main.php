<?php
$at = new ArgsTest();
$at->noneArgs();  //正确

$at->noneArgs(1,2,3,4);  //报Warning，参数过多

$at->oneArgs("sta",123); //报Warning，参数过多

$at->threeArgs();  //报Warning，参数缺失

$at->threeArgs("abb",456,789.11);  //正确

$at->twoArgs();  //报Warning，参数缺失

sleep(1000000);

ReflectionClass::export("ArgsTest");

