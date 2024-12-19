
#include "argument_parser.h"

#include "argument.h"
#include "utils.h"
#include <cassert>

namespace fishc {

ArgumentParser::ArgumentParser(
    const std::vector<Argument> &argument_settings) noexcept
    : argument_settings_(argument_settings) 
    , parsed_args_{InitParsedArgs()}
    , name_to_idx_{InitNameToIdx()}
    , no_opt_names_{InitNoOptNames()} {
}

bool ArgumentParser::Parse(const std::vector<std::string>& args) noexcept {
    // First reset the parsed arguments.
    parsed_args_.clear();
    parsed_args_ = InitParsedArgs();

    // Parse the arguments.

    int no_opt_arg_cnt = 0;

    for (int i = 0; i < static_cast<int>(args.size()); ++i) {
        // first argument is the program name, so skip it.
        if (i == 0) { continue; }

        if (utils::IsOption(args[i])) {
            const auto name = StrToArgFirstName(args[i]);
            if (parsed_args_.count(name) == 0) {
                assert(false && "Maybe validation failed. "
                    "Use ArgumentValidator before ArgumentParser.");  
            }

            if (argument_settings_[name_to_idx_.at(name)].need_value) {
                // If the option needs a value, get the next argument.
                assert(i + 1 < static_cast<int>(args.size()) && 
                    !utils::IsOption(args[i + 1]) &&
                    "Maybe validation failed. "
                    "Use ArgumentValidator before ArgumentParser.");

                parsed_args_[name].push_back(args[i + 1]);
                ++i;

                if (Argument::IsVectorType(
                    argument_settings_[name_to_idx_.at(name)].value_type)) {
                    // If the argument is a vector, need to check the next arguments.
                    while (i + 1 < static_cast<int>(args.size()) && 
                        !utils::IsOption(args[i + 1])) {
                        parsed_args_[name].push_back(args[i + 1]);
                        ++i;
                    }
                }
            } else {
                parsed_args_[name].push_back("");
            }
        } else {
            // If the argument is not an option, we store it in the parsed_args_.
            if (no_opt_arg_cnt >= static_cast<int>(no_opt_names_.size())) {
                assert(false && "Maybe validation failed. "
                    "Use ArgumentValidator before ArgumentParser.");
            }

            parsed_args_[no_opt_names_[no_opt_arg_cnt]].push_back(args[i]);
            ++no_opt_arg_cnt;
        }
    }

    return true;
}

bool ArgumentParser::HasOption(const std::string &option) const noexcept {
    const auto name = StrToArgFirstName(option);
    if (parsed_args_.count(name) == 0) {
        return false;
    }

    return !parsed_args_.at(name).empty();
}

std::string ArgumentParser::StrToArgFirstName(
    const std::string &str) const noexcept {
    for (int i = 0; i < static_cast<int>(argument_settings_.size()); ++i) {
        for (const auto &name : argument_settings_[i].names) {
            if (name == str) {
                return argument_settings_[i].names[0];
            }
        }
    }

    return str;
}

std::map<std::string, std::vector<std::string>> ArgumentParser::InitParsedArgs() const noexcept {
    std::map<std::string, std::vector<std::string>> parsed_args;
    for (const auto &arg_set : argument_settings_) {
        parsed_args[arg_set.names[0]] = {};
    }

    return parsed_args;
}

std::map<std::string, int> ArgumentParser::InitNameToIdx() const noexcept {
    std::map<std::string, int> name_to_idx;
    for (int i = 0; i < static_cast<int>(argument_settings_.size()); ++i) {
        for (const auto &name : argument_settings_[i].names) {
            name_to_idx[name] = i;
        }
    }

    return name_to_idx;
}

std::vector<std::string> ArgumentParser::InitNoOptNames() const noexcept {
    std::vector<std::string> no_opt_names;
    for (const auto &arg_set : argument_settings_) {
        if (!arg_set.is_option) {
            no_opt_names.push_back(arg_set.names[0]);
        }
    }

    return no_opt_names;
}

}  // namespace fishc
