
#include "argument.h"

#include <cassert>

#include "utils.h"

namespace fishc {

Argument::Argument(std::vector<std::string> names, std::string description)
    : names(names)
    , description(description) {
    assert(!names.empty() && "The names must not be empty.");
}

Argument& Argument::SetNeedArgument(
    bool need_argument, std::string argument_name, Type argument_type) {
    assert(need_argument && !argument_name.empty() && 
        "The argument_name must not be empty if need_argument is true.");

    this->need_argument = need_argument;
    this->argument_name = argument_name;
    this->argument_type = argument_type;
    return *this;
}

Argument& Argument::SetIsRequired(
    const bool is_required, const int required_group) {
    this->is_required = is_required;
    this->required_group = required_group;
    return *this;
}

Argument& Argument::SetIsOption(const bool is_option) {
    this->is_option = is_option;

    if (is_option) {
        for (const auto &name : names) {
            assert(utils::IsOption(name) 
                && "The name must be an option.");
        }
    }

    return *this;
}

}  // namespace fishc