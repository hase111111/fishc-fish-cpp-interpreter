
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

    // Validate the arguments.
    if (!argument_validator_.Validate(args)) {
        std::cout << "Invalid arguments: " 
            << argument_validator_.GetErrorReasonString()
            << std::endl;
        return false;
    }

    // If the arguments are valid, parse them.

    // First reset the parsed arguments.
    parsed_args_.clear();
    for (int i = 0; i < static_cast<int>(argument_settings_.size()); ++i) {
        parsed_args_.push_back({false, ""});
    }

    // Parse the arguments.
    for (int i = 0; i < static_cast<int>(args.size()); ++i) {
        for (int j = 0; j < static_cast<int>(argument_settings_.size()); ++j) {
            for (const auto &opt : argument_settings_[j].names) {
                if (args[i] != opt) { continue; }

                parsed_args_[j].first = true;
                if (argument_settings_[j].need_argument) {
                    parsed_args_[j].second = args[i + 1];
                    ++j;
                }
            }
        }
    }

    return true;
}

bool ArgumentParser::HasOption(const std::string &option) const noexcept {
    for (int i = 0; i < static_cast<int>(parsed_args_.size()); ++i) {
        if (!parsed_args_[i].first) { continue; }

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