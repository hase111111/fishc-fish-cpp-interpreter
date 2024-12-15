
#ifndef FISHC_ARGUMENT_PARSER_H_
#define FISHC_ARGUMENT_PARSER_H_

#include <string>
#include <vector>

#include "argument.h"
#include "argument_validator.h"

namespace fishc {

class ArgumentParser final {
  public:
    ArgumentParser() = delete;
    ArgumentParser(const std::vector<Argument> &argument_settings) noexcept;

    ~ArgumentParser() = default;

    bool Parse(int argc, char **argv) noexcept;


 private:
    [[nodiscard]]
    std::vector<Argument> AddHelpOption(
      const std::vector<Argument> &argument_settings) const noexcept;

    [[nodiscard]]
    std::vector<std::string> ArgArrayToVector(int argc, char *argv[]) const;
    
    std::vector<Argument> argument_settings_;
    ArgumentValidator argument_validator_;
};

}  // namespace fishc

#endif  // FISHC_ARGUMENT_PARSER_H_
