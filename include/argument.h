
// Copyright (c) 2024-2025 T.Hasegawa
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php

#ifndef FISHC_ARGUMENT_H_
#define FISHC_ARGUMENT_H_

#include <string>
#include <vector>

namespace fishc {

struct Argument final {
    enum class Type : int {
        kBool,
        kInt,
        kFloat,
        kString,
    };

    Argument() = delete;
    Argument(const std::vector<std::string>& names, 
             const std::string& description) noexcept;
    ~Argument() = default;
    

    // Builder Pattern for Argument.

    [[nodiscard]]
    Argument& NeedValue(
        const std::string& value_name, Type value_type, 
        bool value_is_vector = false) noexcept;

    [[nodiscard]]
    Argument& IsRequired(int required_group) noexcept;

    [[nodiscard]]
    Argument& IsOption() noexcept;

    [[nodiscard]]
    Argument& IsInfoOption() noexcept;


    // Variables.

    //! The names of the argument. Can be multiple names.
    //! If the argument is an option, the name must start with "-".
    //! example: {"-h", "--help"}
    std::vector<std::string> names;

    //! The description displayed in the help menu.
    //! example: "Show help message"
    std::string description;

    //! If true, the option needs a value.
    //! For example, it becomes true 
    //! when you need to specify a value in the form of --number 100.
    bool need_value{ false };

    //! The name of the value displayed when help is used. 
    //! Like -n <number>.
    std::string value_name;

    //! The type of the value.
    Type value_type{ Type::kString };

    bool value_is_vector{ false };

    bool is_required{ false };        //!< If the argument is true, the argument must be provided.
    int required_group{ -1 };         //!< The group number of the required argument.
    bool is_option{ false };          //!< If the argument is true, the argument is an option.
    bool is_info{ false };         //!< If the argument is true, the argument is a special argument.
};

}  // namespace fishc

#endif  // FISHC_ARGUMENT_H_
