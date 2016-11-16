php-coroutine
=============

Extension for php coroutine. _Not Implemented Now_

## Usage
```php
<?php
function bar($c)
{
	Coroutine::yield($c+1);
	Coroutine::yield($c+2);
}

$co = Coroutine::create(function ($a, $b) {
	Coroutine::yield($a);
	$c = Coroutine::yield($b);

	bar($c);
});

echo $co->resume(1, 2); // 1
echo $co->resume();     // 2
echo $co->resume(3);    // 4
echo $co->resume();     // 5
```
