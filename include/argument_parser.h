
// Copyright (c) 2024-2025 T.Hasegawa
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php

#ifndef FISHC_ARGUMENT_PARSER_H_
#define FISHC_ARGUMENT_PARSER_H_

#include <cassert>
#include <map>
#include <string>
#include <vector>

#include "argument.h"
#include "utils.h"

namespace fishc {

class ArgumentParser final {
  public:
    ArgumentParser() = delete;
    ArgumentParser(const std::vector<Argument> &argument_settings) noexcept;

    ~ArgumentParser() = default;

    bool Parse(const std::vector<std::string>& args) noexcept;

    [[nodiscard]]
    bool HasOption(const std::string &option) const noexcept;

    template<typename T>
    [[nodiscard]]
    T GetOptionValue(const std::string &option) const {
        const auto name = StrToArgFirstName(option);
        if (parsed_args_.count(name) == 0) { return T{}; }

        if (argument_settings_[name_to_idx_.at(name)].value_is_vector) {
            assert(false && "The argument is vector type.");
        }

        const auto &values = parsed_args_.at(name);
        if (values.empty()) { return T{}; }

        return utils::StringTo<T>(values[0]);
    }

    template<typename T>
    [[nodiscard]]
    std::vector<T> GetOptionValueVector(const std::string &option) const {
        const auto name = StrToArgFirstName(option);
        if (parsed_args_.count(name) == 0) { return std::vector<T>{}; }

        if (!argument_settings_[name_to_idx_.at(name)].value_is_vector) {
            assert(false && "The argument is not vector type.");
        }

        const auto &values = parsed_args_.at(name);
        std::vector<T> result;
        for (const auto &value : values) {
            result.push_back(utils::StringTo<T>(value));
        }

        return result;
    }

 private:
    std::string StrToArgFirstName(const std::string &str) const noexcept;

    [[nodiscard]]
    std::map<std::string, std::vector<std::string>>
    InitParsedArgs() const noexcept;

    [[nodiscard]]
    std::map<std::string, int> InitNameToIdx() const noexcept;

    [[nodiscard]]
    std::vector<std::string> InitNoOptNames() const noexcept;

    const std::vector<Argument> argument_settings_;
    std::map<std::string, std::vector<std::string>> parsed_args_;
    const std::map<std::string, int> name_to_idx_;
    const std::vector<std::string> no_opt_names_;
};

}  // namespace fishc

#endif  // FISHC_ARGUMENT_PARSER_H_
