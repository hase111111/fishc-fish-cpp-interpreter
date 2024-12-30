
#include <iostream>
#include <string>

#include "argument_help_printer.h"
#include "argument_initializer.h"
#include "argument_parser.h"
#include "argument_validator.h"
#include "file_loader.h"
#include "interpreter.h"
#include "utils.h"
#include "version.h"

int main(int argc, char **argv) {
    // First, parse the command line arguments.

    const auto arg_vec = fishc::utils::ArgArrayToVector(argc, argv);
    const auto argument_setting = fishc::ArgumentInitializer{}.Initialize();
    auto arg_validator = fishc::ArgumentValidator{argument_setting};

    if (!arg_validator.Validate(arg_vec)) {
        // If the command line arguments are invalid, exit the program.
        std::cout << "Error: " << arg_validator.GetErrorReasonString() << std::endl;
        return 1;
    }

    auto arg_parser = fishc::ArgumentParser{argument_setting};

    if (!arg_parser.Parse(arg_vec)) {
        // If parsing fails, exit the program.
        return 2;
    }

    // Parse is successful, so check if the user requested help or version.

    if (arg_parser.HasOption("--help")) {
        // If the user requested help, print the help message and exit.
        fishc::ArgumentHelpPrinter{argument_setting}.Print();
        return 0;
    }

    if (arg_parser.HasOption("--version")) {
        // If the user requested the version, print the version and exit.
        fishc::VersionPrinter{}.Print();
        return 0;
    }

    // If the user provided a script file, read the file and execute the code.
    std::string code = "";

    if (arg_parser.HasOption("--code")) {
        code = arg_parser.GetOptionValue<std::string>("--code");
    } else {
        std::string path = arg_parser.GetOptionValue<std::string>("script");
        fishc::FileLoader file_loader{path};
        if (!file_loader.IsOpen()) {
            std::cout << "Failed to open the file: " << path << std::endl;
            return 3;   
        }

        code = file_loader.GetFile();
    }

    int limit = -1;
    if (arg_parser.HasOption("--limit")) {
        limit = arg_parser.GetOptionValue<int>("--limit");
    }

    bool debug = arg_parser.HasOption("--debug");

    fishc::Interpreter interpreter(code, limit, debug);
    interpreter.Run();

    return 0;
}
