
#include <iostream>

#include "help_printer.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // Print usage
        fishc::HelpPrinter::PrintHelp();
    } else {
        // Read input file
        std::string input_file = argv[1];
        std::cout << "Reading input file: " << input_file << std::endl;
    }

    return 0;
}
