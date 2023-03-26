#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <flags.h>

// The structure, apporoach, and flag-handling code for this project were
// inspired by and taken from [imgcmp](https://github.com/yahiaetman/imgcmp)

int main(int argc, char** argv) {

    std::stringstream HELP;
    HELP 
    << "This file comparison utility is intended for comparing files in a\n"
    << "platform-independant manner during software testing. It will\n"
    << "only return a pass (0) or a fail (-1) and will not provide\n"
    << "information to assist finding the difference (common platform-\n"
    << "dependent utilities can provide more information).\n"
    << "\n"
    << "Usage:\n"
    << "simplediff path_to_file1 path_to_file2 [-v, -verbose] [-h, -help]\n"
    << "\n"
    << "[-v, --verbose] is an optional parameter that causes a message\n"
    << "               to be displayed that reports the comparison results.\n"
    << "[-h, --help]    is an optional parameter that displays this message.";

    flags::args args(argc, argv);
    int status = 0;

    bool verbose = args.get<bool>("v", false)
                          || args.get<bool>("verbose", false);

    if (args.get<bool>("h", false) || args.get<bool>("help", false)) {
        std::cout << HELP.str() << std::endl;
        return status = 0;
    }
    
    auto path1 = args.get<std::string>(0);
    auto path2 = args.get<std::string>(1);

    if (!path1.has_value() || !path2.has_value()) {
        std::cout << "You must specify the paths to the two files to compare."
                  << std::endl << std::endl;
        std::cout << HELP.str() << std::endl;
        return status = -1;
    }

    std::ifstream inFile1(path1.value(), std::ios::in);
    if (!inFile1) {
        std::cout << "Error in opening file " << path1.value() << std::endl;
        return status = -1;
    }
    char c;
    std::stringstream file1Stream;
    while (inFile1.get(c)) {
       file1Stream << c;
    }
    //Debug: std::cout << "File 1 contents:" << std::endl << file1Stream.str();

    std::ifstream inFile2(path2.value(), std::ios::in);
    if (!inFile2) {
        std::cout << "Error in opening file " << path2.value() << std::endl;
        return status = -1;
    }
    std::stringstream file2Stream;
    while (inFile2.get(c)) {
       file2Stream << c;
    }
    //Debug: std::cout << "File 2 contents:" << std::endl << file2Stream.str();

    if (file1Stream.str() == file2Stream.str()) {
        if (verbose) {
            std::cout << "Files are the same" << std::endl;
        }
        return status = 0;
    } else {
        if (verbose) {
            std::cout << "Files are different" << std::endl;
        }
        return status = -1;
    }
}
