
#include "argument_help_printer.h"
#include "argument_initializer.h"
#include "argument_parser.h"
#include "interpreter.h"
#include "version.h"

int main(int argc, char **argv) {
    // First, parse the command line arguments.

    const auto argumenys = fishc::ArgumentInitializer{}.Initialize();
    auto arg_parser = fishc::ArgumentParser{argumenys};

    if (!arg_parser.Parse(argc, argv)) {
        // If the command line arguments are invalid, exit the program.
        return 1;
    }

    fishc::ArgumentHelpPrinter{argumenys}.Print();

    return 0;
    const auto option = arg_parser.GetOption();

    if (option.is_help_mode) {
        return 0;
    } else if (option.is_version_mode) {
        fishc::VersionPrinter::PrintVersion();
        return 0;
    }

    fishc::Interpreter interpreter(option.code);
    interpreter.Run();

    return 0;
}
