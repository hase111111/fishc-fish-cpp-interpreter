
#ifndef FISHC_ARGUMENT_PARSER_H_
#define FISHC_ARGUMENT_PARSER_H_

#include <optional>
#include <string>

#include "option.h"

namespace fishc {

class ArgumentParser final {
  public:
    ArgumentParser() = delete;
    ArgumentParser(int argc, char *argv[]);
    ~ArgumentParser() = default;

    inline bool HasCodePath() const { return code_path_.has_value(); }
    inline std::string GetCodePath() const { return code_path_.value(); }
    inline Option GetOption() const { return Option{}; }

 private:
    int option_num_ = 0;
    std::optional<std::string> code_path_;
};

};  // namespace fishc

#endif  // FISHC_ARGUMENT_PARSER_H_
