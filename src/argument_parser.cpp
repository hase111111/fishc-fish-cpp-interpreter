
#include "argument_parser.h"
#include "file_loader.h"

namespace fishc {

ArgumentParser::ArgumentParser(int argc, char *argv[]) {
    if (argc < 2) {
        // first argument is the program name, so we need at least 2 arguments.
        // activate the help mode.
        option_.is_help_mode = true;
        return;
    }

    // check if the first argument is a code path.
    std::string first_arg = argv[1];

    FileLoader file_loader(first_arg);
    if (file_loader.IsOpen()) {
        option_.code = file_loader.GetFile();
        has_code_ = true;
    }

    int counter = 1;

    while (counter < argc) {
        std::string arg = argv[counter];

        if (IsOption(arg)) {
            const auto mode = ArgToOptionMode(arg);
            ApplyOption(mode);
        }

        counter++;
    }

    // If has not code, actiavte the help mode.
    if (!has_code_) {

        option_.is_help_mode = true;
    }
}

void ArgumentParser::ApplyOption(const OptionMode mode) {
    switch (mode) {
        case OptionMode::kHelp:
            option_.is_help_mode = true;
            option_.is_version_mode = false;
            break;
        case OptionMode::kVersion:
            option_.is_version_mode = true;
            option_.is_help_mode = false;
            break;
        case OptionMode::kCode:
            break;
        case OptionMode::kStack:
            break;
        case OptionMode::kValue:
            break;
        case OptionMode::kTick:
            break;
        case OptionMode::kAlwaysTick:
            break;
        case OptionMode::kUnknown:
            break;
    }
}

}  // namespace fishc