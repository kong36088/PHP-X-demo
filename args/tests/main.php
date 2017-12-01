<?php
$at = new ArgsTest();
$at->noneArgs();

$at->oneArgs("sta",123);

$at->twoArgs("abb",456);

$at->threeArgs("abb",456,789.11);

ReflectionClass::export("ArgsTest");

