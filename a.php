<?php
$a = Coroutine::create(function () {
    echo "a: $a\n";
    echo "b: $b\n";

    return __function__;
});

var_dump($a->getId());
