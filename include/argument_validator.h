
#pragma once

#include <vector>

#include "argument.h"

namespace fishc {

class ArgumentValidator final {
  public:
    enum class ErrorReason : int {
        kUnknownOption,
        kOptionNeedsArgument,
        kUnknownArgument,
    };

    ArgumentValidator() = delete;
    explicit ArgumentValidator(const std::vector<Argument> &argument_settings)
        : argument_settings_(argument_settings) {}

    ~ArgumentValidator() = default;

    bool Validate(int argc, char *argv[]);
    inline std::string GetErrorReasonString() const { return error_reason_str_; }
    inline ErrorReason GetErrorReason() const { return error_reason_; }

private:
    std::vector<Argument> argument_settings_{};
    std::string error_reason_str_{};
    ErrorReason error_reason_{};

    int MatchArgumentIndex(const std::string &arg) const;
    int GetMaxArgNum() const;
};

}  // namespace fishc
