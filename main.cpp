#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <cctype>
#include <flags.h>

// The structure, apporoach, and flag-handling code for this project were
// inspired by and taken from [imgcmp](https://github.com/yahiaetman/imgcmp)

int main(int argc, char** argv) {
    bool debug = false;

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
    char c1;
    std::stringstream file1Stream;
    while (inFile1.get(c1)) {
       file1Stream << c1;
    }
    if (debug) {
        std::cout << "File 1 contents:" << std::endl << file1Stream.str();
    }

    std::ifstream inFile2(path2.value(), std::ios::in);
    if (!inFile2) {
        std::cout << "Error in opening file " << path2.value() << std::endl;
        return status = -1;
    }
    char c2;
    std::stringstream file2Stream;
    while (inFile2.get(c2)) {
       file2Stream << c2;
    }
    if (debug) {
        std::cout << "File 2 contents:" << std::endl << file2Stream.str();
    }

    long numSameNonDigits = 0;
    long numDiffNonDigits = 0;
    long numSameDigits = 0;
    long numDiffDigits = 0;
    while (file1Stream.get(c1)) {
        if (file2Stream.get(c2)) {
            // file2 is treated as the reference file (hence used for isdigit())
            if (debug) {
                std::cout << "Read characters: "
                          << c1 << " (" << static_cast<int>(c1) << ")  "
                          << c2 << " (" << static_cast<int>(c2) << ")"
                          << std::endl;
            }
            if (c1 == c2) {
                if (isdigit(c2)) {
                    numSameDigits++;
                } else {
                    numSameNonDigits++;
                }
            } else {
                if (debug) {
                    std::cout << "Different characters: "
                              << c1 << " (" << static_cast<int>(c1) << ")"
                              << " != "
                              << c2 << " (" << static_cast<int>(c2) << ")"
                              << std::endl;
                }
                if (isdigit(c2)) {
                    numDiffDigits++;
                } else {
                    numDiffNonDigits++;
                }
            }
        } else {
            // If file1 is longer than file2, then add add to number of diffs
            if (debug) {
                std::cout << "File #1 is longer than File #2 with character: "
                      << c1 << " (" << static_cast<int>(c1) << ")" << std::endl;
            }
            if (isdigit(c1)) {
                numDiffDigits++;
            } else {
                numDiffNonDigits++;
            }
        }
    }
    while (file2Stream.get(c2)) {
        // If file2 is longer than file1, then add add to number of diffs
        if (debug) {
            std::cout << "File #2 is longer than File #1 with character: "
                  << c2 << " (" << static_cast<int>(c2) << ")" << std::endl;
        }
        if (isdigit(c2)) {
            numDiffDigits++;
        } else {
            numDiffNonDigits++;
        }
    }
    // TODO: pass digitThreshold and nonDigitThreshold as parameters
    float digitThreshold = 0.0;
    float nonDigitThreshold = 0.0;

    long totalDigits = numSameDigits + numDiffDigits;
    long totalNonDigits = numSameNonDigits + numDiffNonDigits;
    float percentDiffDigits = 0.f;
    float percentDiffNonDigits = 0.f;
    if (totalDigits > 0) {
        percentDiffDigits = 100.f * static_cast<float>(numDiffDigits)
                                        / static_cast<float>(totalDigits);
        if (verbose) {
            std::cout << "Error for digits: " << percentDiffDigits
                      << "% (threshold: " << digitThreshold
                      << "%, Number of digits: " << totalDigits << ")"
                      << std::endl;
        }
    }
    percentDiffNonDigits = 100.f * static_cast<float>(numDiffNonDigits)
                                       / static_cast<float>(totalNonDigits);
    if (verbose) {
        std::cout << "Error for non-digits: " << percentDiffNonDigits
                  << "% (threshold: " << nonDigitThreshold
                  << "%, Number of non-digits: " << totalNonDigits << ")"
                  << std::endl;
    }

    if (percentDiffDigits <= digitThreshold
            && percentDiffNonDigits <= nonDigitThreshold) {
        if (verbose) {
            std::cout << "Files are the same within specified thresholds"
                      << std::endl;
        }
        return status = 0;
    } else {
        if (verbose) {
            std::cout << "Files are different beyond specified thresholds"
                      << std::endl;
        }
        return status = -1;
    }
}

// ASCII Characters:
// See: https://www.ibm.com/docs/en/aix/7.2?topic=adapters-ascii-decimal-hexadecimal-octal-binary-conversion-table
// 10 = linefeed
// 12 = form feed
// 13 = carriage return
// 32 = space
