
#include "argument_validator.h"

#include <cassert>
#include <map>
#include <vector>

#include "argument.h"
#include "utils.h"

namespace fishc::internal {

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

std::string GetRequiredArgumentMessage() {
    return "Required argument is not provided.";
}

}  // namespace fishc::internal

namespace fishc {

ArgumentValidator::ArgumentValidator(const std::vector<Argument> &argument_settings) noexcept
    : argument_settings_(argument_settings) 
    , help_printer_{argument_settings} {
}

bool ArgumentValidator::Validate(const std::vector<std::string>& args) noexcept {
    assert(!args.empty() && "The args must not be empty.");
    
    std::map<int, bool> already_provided;
    const auto not_opt_arg_idx = GetNotOptionArgumentIndexs();
    int not_opt_arg_cnt = 0;

    // Initialize already_provided.
    for (int i = 0; i < static_cast<int>(argument_settings_.size()); ++i) {
        already_provided[i] = false;
    }

    // first argument is the program name, so skip it.
    for (int i = 0; i < static_cast<int>(args.size()); ++i) {
        // first argument is the program name, so skip it.
        if (i == 0) { continue; }

        const std::string arg = args[i];

        if (utils::IsOption(arg.c_str())) {
            // If the argument is an option, check if it is provided.
            const int index = MatchArgumentIndex(arg);
            if (index == -1) {
                error_reason_str_ = internal::GetUnknownOptionMessage(arg);
                return false;
            }

            // If the option is already provided, return an error.
            if (already_provided[index]) {
                error_reason_str_ = internal::GetMultipleOptionMessage(arg);
                return false;
            }
            already_provided[index] = true;

            // If the option needs an argument, check if it is provided.
            if (argument_settings_[index].need_value) {
                if (i + 1 >= static_cast<int>(args.size())) {
                    error_reason_str_ = internal::GetOptionNeedsArgumentMessage(arg);
                    return false;
                } else if (utils::IsOption(args[i + 1])) {
                    error_reason_str_ = internal::GetOptionNeedsArgumentMessage(arg);
                    return false;
                }

                if (argument_settings_[index].value_is_vector) {
                    // If the argument is a vector, need to check the next arguments.
                    ++i;
                    while (i < static_cast<int>(args.size()) && !utils::IsOption(args[i])) {
                        ++i;
                    }
                } else {
                    ++i;
                }
            }
        } else {
            if (not_opt_arg_cnt < static_cast<int>(not_opt_arg_idx.size())) {
                const int index = not_opt_arg_idx[not_opt_arg_cnt];
                already_provided[index] = true;
                ++not_opt_arg_cnt;
            } else {
                error_reason_str_ = internal::GetUnknownArgumentMessage(arg);
                return false;
            }
        }
    }

    // Check if all required arguments are provided.

    // If the special argument is provided, we don't need to check the required group.
    const auto special_arg_idx = GetSpecialArgIdx();

    for (const auto &idx : special_arg_idx) {
        if (already_provided[idx]) {
            return true;
        }
    }

    // If the special argument is not provided, we need to check the required group.
    const auto required_group = GetRequiredGroup();

    for (const auto &group : required_group) {
        bool is_provided = false;
        for (int i = 0; i < static_cast<int>(argument_settings_.size()); ++i) {
            if (argument_settings_[i].required_group == group) {
                if (already_provided[i]) {
                    is_provided = true;
                    break;
                }
            }
        }

        if (!is_provided) {
            error_reason_str_ = internal::GetRequiredArgumentMessage();
            error_reason_str_ += "\n";
            error_reason_str_ += help_printer_.GetUsage();
            return false;
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

std::set<int> ArgumentValidator::GetRequiredGroup() const {
    std::set<int> required_group;
    for (int i = 0; i < static_cast<int>(argument_settings_.size()); ++i) {
        if (argument_settings_[i].is_required) {
            required_group.insert(argument_settings_[i].required_group);
        }
    }

    return required_group;
}

std::set<int> ArgumentValidator::GetSpecialArgIdx() const {
    std::set<int> special_arg_idx;
    for (int i = 0; i < static_cast<int>(argument_settings_.size()); ++i) {
        if (argument_settings_[i].is_info) {
            special_arg_idx.insert(i);
        }
    }

    return special_arg_idx;
}

}  // namespace fishc
