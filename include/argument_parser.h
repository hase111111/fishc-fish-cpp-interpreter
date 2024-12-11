
#ifndef FISHC_ARGUMENT_PARSER_H_
#define FISHC_ARGUMENT_PARSER_H_

#include "option.h"

namespace fishc {

class ArgumentParser final {
  public:
    ArgumentParser() = delete;
    ArgumentParser(int argc, char *argv[]);
    ~ArgumentParser() = default;

    inline Option GetOption() const { return option_; }

 private:
    void ApplyOption(const OptionMode mode);

    Option option_{};
    bool has_code_{false};
};

};  // namespace fishc

#endif  // FISHC_ARGUMENT_PARSER_H_
