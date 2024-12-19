
#include "argument.h"

#include <cassert>

#include "utils.h"

namespace fishc {

Argument::Argument(const std::vector<std::string>& n, 
                   const std::string& desc) noexcept
    : names(n)
    , description(desc) {
    assert(!names.empty() && "The names must not be empty.");
}

Argument& Argument::NeedValue(
    const std::string& v_name, const Type v_type) noexcept {
    assert(!v_name.empty() && 
        "The argument_name must not be empty if need_argument is true.");

    this->need_value = true;
    this->value_name = v_name;
    this->value_type = v_type;
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