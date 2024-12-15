
#include "argument_parser.h"

#include "file_loader.h"

namespace fishc {

ArgumentParser::ArgumentParser(
    const std::vector<Argument> &argument_settings) noexcept
    : argument_settings_(AddHelpOption(argument_settings))
    , argument_validator_{AddHelpOption(argument_settings)} {}

bool ArgumentParser::Parse(int argc, char **argv) noexcept {
    const auto args = ArgArrayToVector(argc, argv);

    if (!argument_validator_.Validate(args)) {
        error_reason_ = argument_validator_.GetErrorReasonString();
        is_loading_success_ = false;
        return false;
    }

    return true;
}

std::vector<Argument> ArgumentParser::AddHelpOption(
    const std::vector<Argument> &argument_settings) const noexcept {
    const auto help_option = Argument{{"-h", "--help"}, "Show help message."}
        .IsOption();
    std::vector<Argument> new_argument_settings = argument_settings;
    new_argument_settings.push_back(help_option);
    return new_argument_settings;
}

std::vector<std::string> ArgumentParser::ArgArrayToVector(
    const int argc, char *argv[]) const {
    std::vector<std::string> args;
    for (int i = 0; i < argc; ++i) {
        args.push_back(argv[i]);
    }
    return args;
}

}  // namespace fishc