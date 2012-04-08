Coderwall C API - libcoderwall
==============================

A simple library to access the coderwall API. It provides data-structures and
functions to make working with coderwall.com API easier from C/C++ applications.


Building the library
--------------------

First ensure you have [`cmake`](http://www.cmake.org/) installed on your machine.
Then, enter the `build` directory (using `cd` for example) and run:

```
cmake .. && make all
```

This should generate the library file `libcoderwall.a` on Unix which you could
then link with your binaries.

Usage
-----

It is easy to write applications that use `libcoderwall`. All you need to do
to get access to the data-structures and function `libcoderwall` provides
is to include the following header file in the source of your application:

```c
#include <coderwall/coderwall.h>

/* Your code follows below ... */
```

Then, when it's time to compile your appication, add the `include` directory to
your c-compiler include path and link aginst `libcoderwall`.

For a practical example on how to use the library with a program, see the `example`
directory which also includes a file to compile the example with `cmake`.

To compile the example, just enter the `build` directory and run:

```
cmake .. && make coderwall_user
```

Then simply use the new program to see information about developers. For example,
to see information about me run (assuming you are in the `build` directory):

```
example/coderwall_user maher4ever
```

Running the unit-tests
----------------------

This library is tested using [`gtest`](http://code.google.com/p/googletest/). To run the tests, enter the `build`
directory and run:

```
cmake .. && make check
```

License
-------

See the included `LICENSE` file.

Author
------

[Maher Sallam](https://github.com/Maher4Ever)
