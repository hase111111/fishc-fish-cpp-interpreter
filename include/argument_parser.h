
#ifndef FISHC_ARGUMENT_PARSER_H_
#define FISHC_ARGUMENT_PARSER_H_

#include <string>

#include "argument.h"
#include "option.h"

namespace fishc {

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
