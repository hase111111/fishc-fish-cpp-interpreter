
#pragma once

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

    // Builder pattern
    Argument& SetNeedArgument(bool need_argument, std::string argument_name = "", 
        Type argument_type = Type::kString);
    Argument& SetIsRequired(bool is_required, int required_group);
    Argument& SetIsOption(bool is_option);

    Argument() = delete;
    Argument(std::vector<std::string> names, std::string description);

    std::vector<std::string> names;  //!< example: {"-h", "--help"}
    std::string description;         //!< example: "Show help message"

    bool need_argument{ false };          //!< If the argument is true, the option needs an argument.
    std::string argument_name;            //!< example: "<script>"
    Type argument_type{ Type::kString };  //!< example: kString

    bool is_required{ false };        //!< If the argument is true, the argument must be provided.
    int required_group{ -1 };         //!< The group number of the required argument.
    bool is_option{ false };          //!< If the argument is true, the argument is an option.

};

}  // namespace fishc
