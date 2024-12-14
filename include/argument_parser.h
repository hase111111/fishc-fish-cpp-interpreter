
#ifndef FISHC_ARGUMENT_PARSER_H_
#define FISHC_ARGUMENT_PARSER_H_

#include <cassert>
#include <string>
#include <vector>

#include "option.h"
#include "utils.h"

namespace fishc {

struct Argument final {
    enum class Type : int {
        kBool,
        kInt,
        kFloat,
        kString,
    };

    Argument() = delete;
    Argument(std::vector<std::string> names, std::string description)
        : names(names), description(description) {
        assert(!names.empty() && "The names must not be empty.");
    }

    std::vector<std::string> names;  //!< example: {"-h", "--help"}
    std::string description;         //!< example: "Show help message"

    bool need_argument{ false };          //!< If the argument is true, the option needs an argument.
    std::string argument_name;            //!< example: "<script>"
    Type argument_type{ Type::kString };  //!< example: kString

    bool is_required{ false };        //!< If the argument is true, the argument must be provided.
    bool is_option{ false };          //!< If the argument is true, the argument is an option.

    // Builder pattern
    Argument& SetNeedArgument(bool need_argument, std::string argument_name = "", Type argument_type = Type::kString) {
        assert(need_argument && !argument_name.empty() && 
          "The argument_name must not be empty if need_argument is true.");

        this->need_argument = need_argument;
        this->argument_name = argument_name;
        this->argument_type = argument_type;
        return *this;
    }

    Argument& SetIsRequired(bool is_required) {
        this->is_required = is_required;
        return *this;
    }

    Argument& SetIsOption(bool is_option) {
        this->is_option = is_option;

        if (is_option) {
            for (const auto &name : names) {
                assert(utils::IsOption(name.c_str()) && "The name must be an option.");
            }
        }

        return *this;
    }
};

class ArgumentParser final {
  public:
    ArgumentParser() = delete;
    ArgumentParser(int argc, char *argv[]);
    ~ArgumentParser() = default;

    void add_argument(const Argument &argument);

    inline Option GetOption() const { return option_; }
    inline bool IsLoadingSuccess() const { return is_loading_success_; }
    inline std::string GetErrorReason() const { return error_reason_; }

 private:
    bool is_loading_success_{false};
    std::string error_reason_{};
    Option option_{};
    bool has_code_{false};
};

}  // namespace fishc

#endif  // FISHC_ARGUMENT_PARSER_H_
