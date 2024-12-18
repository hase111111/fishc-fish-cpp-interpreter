
#ifndef FISHC_ARGUMENT_PARSER_H_
#define FISHC_ARGUMENT_PARSER_H_

#include <string>
#include <vector>

#include "argument.h"
#include "argument_validator.h"
#include "utils.h"

namespace fishc {

class ArgumentParser final {
  public:
    ArgumentParser() = delete;
    ArgumentParser(const std::vector<Argument> &argument_settings) noexcept;

    ~ArgumentParser() = default;

    bool Parse(int argc, char **argv) noexcept;

    [[nodiscard]]
    bool HasOption(const std::string &option) const noexcept;

    template<typename T>
    [[nodiscard]] 
    T GetOptionValue(const std::string &option) const {
        for (int i = 0; i < static_cast<int>(parsed_args_.size()); ++i) {
            if (!parsed_args_[i].first) { continue; }

            for (const auto &opt : argument_settings_[i].names) {
                if (opt == option) {
                  return utils::StringTo<T>(parsed_args_[i].second);
                }
            }
        }

      return T{};
    }

 private:
    [[nodiscard]]
    std::vector<std::string> ArgArrayToVector(int argc, char *argv[]) const;
    
    const std::vector<Argument> argument_settings_;
    ArgumentValidator argument_validator_;
    std::vector<std::pair<bool, std::string>> parsed_args_;
};

}  // namespace fishc

#endif  // FISHC_ARGUMENT_PARSER_H_
