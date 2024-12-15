
#include <iostream>

#include "argument_parser.h"
#include "argument_parser_initializer.h"
#include "help_printer.h"
#include "interpreter.h"
#include "version.h"

int main(int argc, char **argv) {
    using fishc::ArgumentParser;
    using fishc::ArgumentParserInitializer;
    using fishc::HelpPrinter;
    using fishc::Interpreter;
    using fishc::VersionPrinter;

    auto arg_parser = ArgumentParserInitializer{}.Initialize();

    arg_parser.Parse(argc, argv);

    if (!arg_parser.IsLoadingSuccess()) {
        std::cout << "Arg parser failed: " << arg_parser.GetErrorReason() << std::endl;
        return 1;
    }

    const auto option = arg_parser.GetOption();

    if (option.is_help_mode) {
        HelpPrinter::PrintHelp();
        return 0;
    } else if (option.is_version_mode) {
        VersionPrinter::PrintVersion();
        return 0;
    }

    Interpreter interpreter(option.code);
    interpreter.Run();

    return 0;
}
