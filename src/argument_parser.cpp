
#include "argument_parser.h"

#include <iostream>

#include "argument.h"

namespace fishc {

ArgumentParser::ArgumentParser(
    const std::vector<Argument> &argument_settings) noexcept
    : argument_settings_(argument_settings)
    , argument_validator_{argument_settings} {
}

bool ArgumentParser::Parse(int argc, char **argv) noexcept {
    const auto args = ArgArrayToVector(argc, argv);

    if (!argument_validator_.Validate(args)) {
        std::cout << "Invalid arguments: " << argument_validator_.GetErrorReasonString()
                  << std::endl;
        return false;
    }

    return true;
}

bool ArgumentParser::HasOption(const std::string &option) const noexcept {
    for (int i = 0; i < static_cast<int>(parsed_arguments_.size()); ++i) {
        if (!parsed_arguments_[i].first) { continue; }

        for (const auto &opt : argument_settings_[i].names) {
            if (opt == option) {
                return true;
            }
        }
    }

    return false;
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