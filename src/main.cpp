
#include <iostream>

#include "help_printer.h"
#include "argument_parser.h"

int main(int argc, char *argv[]) {
    using fishc::HelpPrinter;
    using fishc::ArgumentParser;

    ArgumentParser arg_parser(argc, argv);

    if (arg_parser.GetOptionNum() == 0) {
        // if no option is specified, print help and exit.
        std::cout << "No option is specified." << std::endl;
        HelpPrinter::PrintHelp();

        return 0;
    }

    return 0;
}
