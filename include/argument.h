
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
    Argument(std::vector<std::string> names, std::string description) noexcept;
    ~Argument() = default;
    
    // Builder pattern
    Argument& NeedArgument(
        const std::string& argument_name, Type argument_type) noexcept;
    Argument& IsRequired(int required_group) noexcept;
    Argument& IsOption() noexcept;
    Argument& IsSpecial() noexcept;

    std::vector<std::string> names;  //!< example: {"-h", "--help"}
    std::string description;         //!< example: "Show help message"

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
