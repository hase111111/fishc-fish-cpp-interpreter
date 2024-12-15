
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

    // First, parse the command line arguments.

    auto arg_parser = ArgumentParserInitializer{}.Initialize();

    if (!arg_parser.Parse(argc, argv)) {
        // If the command line arguments are invalid, exit the program.
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
