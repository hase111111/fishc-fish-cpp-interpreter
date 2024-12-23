
// Copyright (c) 2024-2025 T.Hasegawa
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php

#ifndef FISHC_ARGUMENT_VALIDATOR_H_
#define FISHC_ARGUMENT_VALIDATOR_H_

#include <set>
#include <string>
#include <vector>

#include "argument.h"
#include "argument_help_printer.h"

namespace fishc {

class ArgumentValidator final {
  public:
    ArgumentValidator() = delete;
    explicit ArgumentValidator(const std::vector<Argument> &argument_settings) noexcept;

    ~ArgumentValidator() = default;

    bool Validate(const std::vector<std::string>& args) noexcept;

    [[nodiscard]]
    inline std::string GetErrorReasonString() const noexcept {
        return error_reason_str_;
    }

private:
    std::vector<Argument> argument_settings_{};
    std::string error_reason_str_{};
    ArgumentHelpPrinter help_printer_;

    int MatchArgumentIndex(const std::string &arg) const;
    std::vector<int> GetNotOptionArgumentIndexs() const;
    std::set<int> GetRequiredGroup() const;
    std::set<int> GetSpecialArgIdx() const;
};

}  // namespace fishc

#endif  // FISHC_ARGUMENT_VALIDATOR_H_
