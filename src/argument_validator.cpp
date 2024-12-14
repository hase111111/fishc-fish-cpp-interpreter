
#include "argument_validator.h"

#include <map>

#include "utils.h"

namespace fishc {

std::string GetUnknownOptionMessage(const std::string &arg) {
    return "Unknown option: " + arg + 
        ". You can use -h or --help to show the help.";
}

std::string GetOptionNeedsArgumentMessage(const std::string &arg) {
    return "Option " + arg + " needs an argument.";
}

bool ArgumentValidator::Validate(int argc, char *argv[]) {
    // first argument is the program name, so we skip it.
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];

        if (utils::IsOption(arg.c_str())) {
            const int index = MatchArgumentIndex(arg);
            if (index == -1) {
                error_reason_str_ = GetUnknownOptionMessage(arg);
                return false;
            }

            // If the option needs an argument, we check if it is provided.
            if (argument_settings_[index].need_argument) {
                if (i + 1 >= argc) {
                    error_reason_str_ = GetOptionNeedsArgumentMessage(arg);
                    return false;
                } else if (utils::IsOption(argv[i + 1])) {
                    error_reason_str_ = GetOptionNeedsArgumentMessage(arg);
                    return false;
                }

                ++i;
            }
        } else {
            // If the argument is not an option, we check if it is required.
            bool is_required = false;
            for (const auto &arg_setting : argument_settings_) {
                if (arg_setting.is_option) { continue; }

                if (arg_setting.is_required) {
                    is_required = true;
                    break;
                }
            }

            if (!is_required) {
                error_reason_str_ = "Unknown argument: " + arg;
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

int ArgumentValidator::GetMaxArgNum() const {
    int max_arg_num = 0;
    for (const auto &arg_setting : argument_settings_) {
        if (!arg_setting.is_option) {
            ++max_arg_num;
        }
    }

    return max_arg_num;
}

}  // namespace fishc
