# simplediff

A simple command line tool written in C++ to compare two text files in a platform-independent manner during software testing. It will only return a pass (0) or a fail (-1) and will not provide information to assist finding what the actual differences are (common platform-dependent utilities can be used to investigate once `simplediff` has identified a difference in automated tests).


## How it works

The contents of the files are read into std::stringstream objects, which are then compared.


## Usage

simplediff `path_to_file1` `path_to_file2` `[-v, -verbose]` `[-h, -help]`

    `[-v, -verbose]` is an optional parameter that causes a message
                     to be displayed that reports the comparison results.
    `[-h, -help]`    is an optional parameter that displays this message.


## Building

    git clone https://github.dom/estrac/simplediff
    mkdir sdiffRelease
    cd sdiffRelease
    cmake -DCMAKE_BUILD_TYPE=Release ../simplediff


## Examples and Tests

After building, running the tests from the `tests` directory in Ubuntu should yield the following results:

    ../bin/simplediff test1.dat test2.dat --verbose -> `Files are the same`
    ../bin/simplediff test1.dat test3.dat --verbose -> `Files are different`
    ../bin/simplediff test1.dat test4.dat --verbose -> `Files are different`


## Credits

The structure, apporoach, and flag-handling code were inspired by and taken from [imgcmp](https://github.com/yahiaetman/imgcmp)
