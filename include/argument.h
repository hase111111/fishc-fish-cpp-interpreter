
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
        kVectorInt,
    };

    Argument() = delete;
    Argument(const std::vector<std::string>& names, 
             const std::string& description) noexcept;
    ~Argument() = default;
    

    // Builder Pattern for Argument.

    [[nodiscard]]
    Argument& NeedArgument(
        const std::string& argument_name, Type argument_type) noexcept;

    [[nodiscard]]
    Argument& IsRequired(int required_group) noexcept;

    [[nodiscard]]
    Argument& IsOption() noexcept;

    [[nodiscard]]
    Argument& IsSpecial() noexcept;


    // Variables.

    //! The names of the argument. Can be multiple names.
    //! If the argument is an option, the name must start with "-".
    //! example: {"-h", "--help"}
    std::vector<std::string> names;

    //! The description displayed in the help menu.
    //! example: "Show help message"
    std::string description;

    bool need_argument{ false };          //!< If the argument is true, the option needs an argument.
    std::string argument_name;            //!< example: "script"
    Type argument_type{ Type::kString };  //!< example: kString

    bool is_required{ false };        //!< If the argument is true, the argument must be provided.
    int required_group{ -1 };         //!< The group number of the required argument.
    bool is_option{ false };          //!< If the argument is true, the argument is an option.
    bool is_special{ false };         //!< If the argument is true, the argument is a special argument.
};

}  // namespace fishc

#endif  // FISHC_ARGUMENT_H_
