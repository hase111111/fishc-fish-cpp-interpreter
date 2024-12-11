
#include <iostream>

#include "argument_parser.h"
#include "file_loader.h"
#include "help_printer.h"
#include "version.h"

int main(int argc, char *argv[]) {
    using fishc::ArgumentParser;
    using fishc::HelpPrinter;
    using fishc::VersionPrinter;

    ArgumentParser arg_parser(argc, argv);

    const auto option = arg_parser.GetOption();

    if (option.is_help_mode) {
        HelpPrinter::PrintHelp();
        return 0;
    } else if (option.is_version_mode) {
        VersionPrinter::PrintVersion();
        return 0;
    }

    return 0;
}
