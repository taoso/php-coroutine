--TEST--
Check for coroutine once resume
--SKIPIF--
<?php if (!extension_loaded("coroutine")) print "skip"; ?>
--FILE--
<?php
$a = Coroutine::create(function ($a, $b) {
    echo "a: $a\n";
    echo "b: $b\n";

    return 'c: ' . ($a + $b);
});

echo $a->resume(1, 2);
?>
--EXPECT--
a: 1
b: 2
c: 3
