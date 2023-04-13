# simplediff

A simple command line tool written in C++17 to compare two text files in a platform-independent manner during software testing. It will only return a pass (0) or a fail (-1) and will not provide information to assist finding the nature of any differences encountered -- common platform-dependent utilities can be used to investigate once `simplediff` has identified a difference in automated tests.

Thresholds can be provided for either digits (0-9) or alpha (a-z, A-Z), and can specify either the number of digits or characters, or a percent of each allowed (by adding the `%` symbol directly after the number).

`simplediff` has been tested on Windows with MSVC and MinGW, and on Ubuntu with the GNU g++ compiler. It should also run on MacOS (but has not yet been tested on that platform). Instructions are currently only for Ubuntu.


## How it works

The contents of the files are each read into a `std::stringstream object`, and then the individual characters are then compared and counted.


## Usage

    simplediff file1 file2 [-v, --verbose] [-d digits[%]] [-a alpha[%]] [-h, --help]

    [-v, --verbose] is an optional parameter that causes a message
                    to be displayed that reports the comparison results.
    [-d digits[%]]  is an optional parameter that sets the number of
                    digits allowed to be different, or, if `%` is added,
                    then the percent of digits allowed to be different.
                    `digits` is a number. Default: 0.
    [-a alpha[%]]   is an optional parameter that sets the number of
                    alpha characters allowed to be different, or, if `%`
                    is added, then the percent of alpha characters allowed
                    to be different. `digits` is a number. Default: 0.
    [-h, --help]    is an optional parameter that displays this message.


## Building on Ubuntu

    git clone --recurse-submodules https://github.dom/estrac/simplediff
    mkdir sdiff_release
    cd sdiff_release
    cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SIMPLEDIFF_TESTS=ON ../simplediff
    cmake --build .


## Tests and Examples on Ubuntu

    ctest

The tests also serve as examples. Manually run them from the `tests` directory and expect the following results:

`../bin/simplediff test_base.txt test1.txt --verbose` *-> Files are the same*  
`../bin/simplediff test_base.txt test2.txt --verbose` *-> Files are different*  
`../bin/simplediff test_base.txt test3.txt --verbose` *-> Files are different*
`../bin/simplediff digits_base.txt digits1.txt -v` *-> Files are the same*  
`../bin/simplediff digits_base.txt digits2.txt -v -d 4% -a 2%` *-> Files same*  
`../bin/simplediff digits_base.txt digits3.txt -v -d 1 -a 1` *-> Files different*

## Credits

The structure, apporoach, and flag-handling code for this project were inspired by and taken from [imgcmp](https://github.com/yahiaetman/imgcmp). Together these utilities provide key utilities for software regression testing (comparing images and comparing text files).
