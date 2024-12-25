
// Copyright (c) 2024-2025 T.Hasegawa
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php

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
    const std::string& v_name, const Type v_type, const bool is_vec) noexcept {
    assert(!v_name.empty() && 
        "The value_name must not be empty if need_value is true.");

    this->need_value = true;
    this->value_name = v_name;
    this->value_type = v_type;
    this->value_is_vector = is_vec;
    return *this;
}

Argument& Argument::IsRequired(const int required_group) noexcept {
    this->is_required = false;
    this->required_group = required_group;
    return *this;
}

Argument& Argument::IsOption() noexcept {
    this->is_option = true;

    for (const auto &name : names) {
        assert(utils::IsOption(name) 
            && "The name must be an option.");
    }

    return *this;
}

Argument& Argument::IsInfoOption() noexcept {
    assert(is_option 
        && "The argument must be an option."
           "Use IsOption() before using IsInfoOption().");

    this->is_info = true;
    return *this;
}

}  // namespace fishc