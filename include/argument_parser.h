
#ifndef FISHC_ARGUMENT_PARSER_H_
#define FISHC_ARGUMENT_PARSER_H_

#include <string>
#include <vector>

#include "argument.h"
#include "argument_validator.h"
#include "option.h"

namespace fishc {

class ArgumentParser final {
  public:
    ArgumentParser() = delete;
    ArgumentParser(const std::vector<Argument> &argument_settings);

    ~ArgumentParser() = default;

    bool Parse(int argc, char *argv[]);

    inline Option GetOption() const { return option_; }
    inline bool IsLoadingSuccess() const { return is_loading_success_; }
    inline std::string GetErrorReason() const { return error_reason_; }

 private:
    std::vector<Argument> AddHelpOption(const std::vector<Argument> &argument_settings);
    
    std::vector<Argument> argument_settings_;
    ArgumentValidator argument_validator_;

    bool is_loading_success_{false};
    std::string error_reason_{};
    Option option_{};
    bool has_code_{false};
};

}  // namespace fishc

#endif  // FISHC_ARGUMENT_PARSER_H_
