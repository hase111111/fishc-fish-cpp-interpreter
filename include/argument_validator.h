
#pragma once

#include <string>
#include <vector>

#include "argument.h"

namespace fishc {

class ArgumentValidator final {
  public:
    enum class ErrorReason : int {
        kUnknownOption,
        kOptionNeedsArgument,
        kUnknownArgument,
        kMultipleOption,
    };

    ArgumentValidator() = delete;
    explicit ArgumentValidator(const std::vector<Argument> &argument_settings);

    ~ArgumentValidator() = default;

    bool Validate(const std::vector<std::string>& args);
    inline std::string GetErrorReasonString() const { return error_reason_str_; }
    inline ErrorReason GetErrorReason() const { return error_reason_; }

private:
    std::vector<Argument> argument_settings_{};
    std::string error_reason_str_{};
    ErrorReason error_reason_{};

    int MatchArgumentIndex(const std::string &arg) const;
    std::vector<int> GetNotOptionArgumentIndexs() const;
};

}  // namespace fishc
