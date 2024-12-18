
#include <string>

#include "argument_help_printer.h"
#include "argument_initializer.h"
#include "argument_parser.h"
#include "interpreter.h"
#include "version.h"

int main(int argc, char **argv) {
    // First, parse the command line arguments.

    const auto arguments = fishc::ArgumentInitializer{}.Initialize();
    auto arg_parser = fishc::ArgumentParser{arguments};

    if (!arg_parser.Parse(argc, argv)) {
        // If the command line arguments are invalid, exit the program.
        return 1;
    }

    if (arg_parser.HasOption("--help")) {
        // If the user requested help, print the help message and exit.
        fishc::ArgumentHelpPrinter{arguments}.Print();
        return 0;
    }

    if (arg_parser.HasOption("--version")) {
        // If the user requested the version, print the version and exit.
        fishc::VersionPrinter{}.Print();
        return 0;
    }

    // If the user provided a script file, read the file and execute the code.
    std::string code = "'Hello, World!' rooooo oo oooooo ao;";

    if (arg_parser.HasOption("--code")) {
        code = arg_parser.GetOptionValue<std::string>("--code");
    } else {
        std::string path = arg_parser.GetOptionValue<std::string>("script");
    }

    fishc::Interpreter interpreter(code);
    interpreter.Run();

    return 0;
}
