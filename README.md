# simplediff

A simple command line tool written in C++ to compare two text files in a platform-independent manner during software testing. It will only return a pass (0) or a fail (-1) and will not provide information to assist finding the difference (common platform-dependent utilities can provide more information).

## How it works

The contents of the files are read into std::stringstream objects, which are then compared.

## Usage

simplediff `path_to_file1` `path_to_file2` `[-v, -verbose]` `[-h, -help]`

    `[-v, -verbose]` is an optional parameter that causes a message
                     to be displayed that reports the comparison results.
    `[-h, -help]`    is an optional parameter that displays this message.

## Examples and Tests

Running the tests from the installation directory in Ubuntu should yield the following results:

bin/simplediff tests/test1.dat tests/test2.dat --verbose -> `Files are the same`
bin/simplediff tests/test1.dat tests/test3.dat --verbose -> `Files are different`
bin/simplediff tests/test1.dat tests/test4.dat --verbose -> `Files are different`

## Credits

The structure, apporoach, and flag-handling code were inspired by and taken from [imgcmp](https://github.com/yahiaetman/imgcmp)
