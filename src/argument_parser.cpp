
#include "argument_parser.h"
#include "file_loader.h"

namespace fishc {

ArgumentParser::ArgumentParser(const std::vector<Argument> &argument_settings)
    : argument_settings_(AddHelpOption(argument_settings))
    , argument_validator_{AddHelpOption(argument_settings)} {
}

bool ArgumentParser::Parse(int argc, char *argv[]) {
    if (argc < 2) {
        // first argument is the program name, so we need at least 2 arguments.
        // activate the help mode.
        option_.is_help_mode = true;
        is_loading_success_ = true;
        return false;
    }

    // check if the first argument is a code path.
    std::string first_arg = argv[1];

    if (!IsOption(first_arg)) {
        FileLoader file_loader(first_arg);
        if (file_loader.IsOpen()) {
            option_.code = file_loader.GetFile();
            has_code_ = true;
        } else {
            // if the file is not loaded, end the program.
            is_loading_success_ = false;
            error_reason_ = "Failed to load the file: " + first_arg;
            return false;
        }
    }

    int counter = 1;

    while (counter < argc) {
        std::string arg = argv[counter];

        if (IsOption(arg)) {
            const auto mode = ArgToOptionMode(arg);

            switch (mode) {
            case OptionMode::kHelp: {
                option_.is_help_mode = true;
                option_.is_version_mode = false;
                break;
            }
            case OptionMode::kVersion: {
                option_.is_help_mode = false;
                option_.is_version_mode = true;
                break;
            }
            case OptionMode::kCode: {
                std::string code;
                if (counter + 1 < argc) {
                    code = argv[counter + 1];
                } else {
                    // if the code is not loaded, end the program.
                    is_loading_success_ = false;
                    error_reason_ = "-c, --code requires a code path.";
                    return false;
                }

                // if the code is already loaded, skip this argument.
                if (!has_code_) {
                    option_.code = code;
                    has_code_ = true;
                }

                break;
            }
            case OptionMode::kStack: {
                if (counter + 1 < argc) {
                    std::string stack = argv[counter + 1];
                    option_.initial_stack = stack;
                } else {
                    // if the stack is not loaded, end the program.
                    is_loading_success_ = false;
                    error_reason_ = "-s, --stack requires a stack value.";
                    return false;
                }
                break;
            }
            case OptionMode::kValue: {
                if (counter + 1 < argc) {
                    std::string value = argv[counter + 1];
                    option_.initial_value = value;
                } else {
                    // if the value is not loaded, end the program.
                    is_loading_success_ = false;
                    error_reason_ = "-v, --value requires a value.";
                    return false;
                }
                break;
            }
            case OptionMode::kTick: {
                if (counter + 1 < argc) {
                    std::string tick = argv[counter + 1];
                    option_.tick = std::stoi(tick);
                } else {
                    // if the tick is not loaded, end the program.
                    is_loading_success_ = false;
                    error_reason_ = "-t, --tick requires a tick value (int).";
                    return false;
                }
                break;
            }
            case OptionMode::kAlwaysTick: {
                option_.always_tick = true;
                break;
            }
            default:{
                // if the option is not recognized, end the program.
                is_loading_success_ = false;
                error_reason_ = "Unknown option: " + arg;
                return false;
            }
            }
        }


        counter++;
    }

    // If has not code, actiavte the help mode.
    if (!has_code_ && !option_.is_help_mode && !option_.is_version_mode) {
        option_.is_help_mode = true;
    }

    is_loading_success_ = true;

    return true;
}

std::vector<Argument> ArgumentParser::AddHelpOption(const std::vector<Argument> &argument_settings) {
    const auto help_option = Argument{{"-h", "--help"}, "Show help message."}
        .SetIsOption(true);
    std::vector<Argument> new_argument_settings = argument_settings;
    new_argument_settings.push_back(help_option);
    return new_argument_settings;
}

}  // namespace fishc