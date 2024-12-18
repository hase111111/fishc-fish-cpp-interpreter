
#include "argument.h"

#include <cassert>

#include "utils.h"

namespace fishc {

Argument::Argument(std::vector<std::string> names, std::string description) noexcept
    : names(names)
    , description(description) {
    assert(!names.empty() && "The names must not be empty.");
}

Argument& Argument::NeedArgument(
    const std::string& argument_name, const Type argument_type) noexcept {
    assert(!argument_name.empty() && 
        "The argument_name must not be empty if need_argument is true.");

    this->need_argument = true;
    this->argument_name = argument_name;
    this->argument_type = argument_type;
    return *this;
}

Argument& Argument::IsRequired(const int required_group) noexcept {
    this->is_required = true;
    this->required_group = required_group;
    return *this;
}

Argument& Argument::IsOption() noexcept {
    this->is_option = true;

    if (is_option) {
        for (const auto &name : names) {
            assert(utils::IsOption(name) 
                && "The name must be an option.");
        }
    }

    return *this;
}

Argument& Argument::IsSpecial() noexcept {
    this->is_special = true;
    return *this;
}

}  // namespace fishc