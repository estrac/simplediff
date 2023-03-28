# simplediff

A simple command line tool written in C++17 to compare two text files in a platform-independent manner during software testing. It will only return a pass (0) or a fail (-1) and will not provide information to assist finding the nature of any differences encountered -- common platform-dependent utilities can be used to investigate once `simplediff` has identified a difference in automated tests.

`simplediff` has been tested on Windows with MSVC and MinGW, and on Ubuntu with the GNU g++ compiler. It should also run on MacOS (but has not yet been tested there). Instructions are currently only for Ubuntu.


## How it works

The contents of the files are read into `std::stringstream objects`, which are then compared.


## Usage

    simplediff path_to_file1 path_to_file2 [-v, --verbose] [-h, --help]

    [-v, --verbose] is an optional parameter that causes a message
                    to be displayed that reports the comparison results.
    [-h, --help]    is an optional parameter that displays this message.


## Building on Ubuntu

    git clone --recurse-submodules https://github.dom/estrac/simplediff
    mkdir sdiff_release
    cd sdiff_release
    cmake -DCMAKE_BUILD_TYPE=Release ../simplediff
    cmake --build .


## Tests and Examples on Ubuntu

    ctest

The tests also serve as examples. Manually run them from the `tests` directory and expect the following results:

   `../bin/simplediff test_base.txt test1.txt --verbose` *-> Files are the same*
   `../bin/simplediff test_base.txt test2.txt --verbose` *-> Files are different*
   `../bin/simplediff test_base.txt test3.txt --verbose` *-> Files are different*


## Credits

The structure, apporoach, and flag-handling code for this project were inspired by and taken from [imgcmp](https://github.com/yahiaetman/imgcmp)
