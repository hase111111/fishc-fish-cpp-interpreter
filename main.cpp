
#include <iostream>

#include "argument.h"
#include "argument_parser.h"
#include "help_printer.h"
#include "interpreter.h"
#include "version.h"

int main(int argc, char *argv[]) {
    using fishc::Argument;
    using fishc::ArgumentParser;
    using fishc::HelpPrinter;
    using fishc::Interpreter;
    using fishc::VersionPrinter;

    const auto code_argument = 
        Argument{{"-c", "--code"}, "Set the code."}
        .SetNeedArgument(true, "<code>", Argument::Type::kString);

    const auto tick_argument = 
        Argument{{"-t", "--tick"}, "Set the tick value (millisecond)."}
        .SetNeedArgument(true, "<tick>", Argument::Type::kInt);

    ArgumentParser arg_parser({code_argument, tick_argument});

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
