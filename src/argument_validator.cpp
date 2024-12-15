
#include "argument_validator.h"

#include <map>
#include <vector>

#include "utils.h"

namespace fishc {

std::string GetUnknownOptionMessage(const std::string &arg) {
    return "Unknown option: " + arg + 
        ". You can use -h or --help to show the help.";
}

std::string GetOptionNeedsArgumentMessage(const std::string &arg) {
    return "Option " + arg + " needs an argument.";
}

std::string GetUnknownArgumentMessage(const std::string &arg) {
    return "Unknown argument: " + arg;
}

std::string GetMultipleOptionMessage(const std::string &arg) {
    return "Option " + arg + " is provided multiple times.";
}

ArgumentValidator::ArgumentValidator(const std::vector<Argument> &argument_settings)
    : argument_settings_(argument_settings) {
}

bool ArgumentValidator::Validate(const std::vector<std::string>& args) {
    std::map<int, bool> already_provided;
    const auto not_option_argument_indexs = GetNotOptionArgumentIndexs();
    int not_option_argument_count = 0;

    // first argument is the program name, so skip it.
    for (int i = 1; i < static_cast<int>(args.size()); ++i) {
        const std::string arg = args[i];

        if (utils::IsOption(arg.c_str())) {
            // If the argument is an option, check if it is provided.
            const int index = MatchArgumentIndex(arg);
            if (index == -1) {
                error_reason_str_ = GetUnknownOptionMessage(arg);
                error_reason_ = ErrorReason::kUnknownOption;
                return false;
            }

            // If the option is already provided, return an error.
            if (already_provided.find(index) != already_provided.end()) {
                error_reason_str_ = GetMultipleOptionMessage(arg);
                error_reason_ = ErrorReason::kMultipleOption;
                return false;
            }
            already_provided[index] = true;

            // If the option needs an argument, check if it is provided.
            if (argument_settings_[index].need_argument) {
                if (i + 1 >= static_cast<int>(args.size())) {
                    error_reason_str_ = GetOptionNeedsArgumentMessage(arg);
                    error_reason_ = ErrorReason::kOptionNeedsArgument;
                    return false;
                } else if (utils::IsOption(args[i + 1])) {
                    error_reason_str_ = GetOptionNeedsArgumentMessage(arg);
                    error_reason_ = ErrorReason::kOptionNeedsArgument;
                    return false;
                }

                ++i;
            }
        } else {
            if (not_option_argument_count < static_cast<int>(not_option_argument_indexs.size())) {
                const int index = not_option_argument_indexs[not_option_argument_count];
                already_provided[index] = true;
                ++not_option_argument_count;
            } else {
                error_reason_str_ = GetUnknownArgumentMessage(arg);
                error_reason_ = ErrorReason::kUnknownArgument;
                return false;
            }
        }
    }

    return true;
}

int ArgumentValidator::MatchArgumentIndex(const std::string &arg) const {
    for (int i = 0; i < static_cast<int>(argument_settings_.size()); ++i) {
        // If the argument is not an option, we skip it.
        if (!argument_settings_[i].is_option) { continue; }

        for (const auto &name : argument_settings_[i].names) {
            if (arg == name) {
                return i;
            }
        }
    }

    return -1;
}

std::vector<int> ArgumentValidator::GetNotOptionArgumentIndexs() const {
    std::vector<int> not_option_argument_indexs;
    for (int i = 0; i < static_cast<int>(argument_settings_.size()); ++i) {
        if (!argument_settings_[i].is_option) {
            not_option_argument_indexs.push_back(i);
        }
    }

    return not_option_argument_indexs;
}

}  // namespace fishc
