# mio\_logger
> A C Extension for PHP log, goal is fast,

## Usage
```php

$mio_log = new MioLogger("mio", "path_to.log");

$channel = $mio_log->getChannel() // "mio";
$path = $mio_log->getPath(); // "path_go.log";

$mio_log->setChannel("amaze");
$mio_log->setPath("/home/you_home/amaze.log");

$mio_log->emergency("Oh No");   // write log with emergency level
$mio_log->alert("Oh No");       // write log with alert level
$mio_log->critical("Oh No");    // write log with critical level
$mio_log->error("Oh No");       // write log with error leve
$mio_log->warning("Oh No");     // write log with warning level
$mio_log->info("Oh No");        // write log with info level
$mio_log->debug("Oh No");       // write log with debug level

```

## Return value
1. -2   can't open or crate the log file
2. -1   can't write log
3. 0    success
