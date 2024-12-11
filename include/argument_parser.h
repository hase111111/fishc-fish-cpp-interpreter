
#ifndef FISHC_ARGUMENT_PARSER_H_
#define FISHC_ARGUMENT_PARSER_H_

#include <optional>
#include <string>

namespace fishc {

enum class Option : int {
    kHelp = 0,
    kVersion,
    kCode,
    kStack,
    kValue,
    kTick,
    kAlwaysTick,
    kUnknown
};

class ArgumentParser final {
  public:
    ArgumentParser() = delete;
    ArgumentParser(int argc, char *argv[]);
    ~ArgumentParser() = default;

    inline bool HasCodePath() const { return code_path_.has_value(); }
    inline std::string GetCodePath() const { return code_path_.value(); }
    constexpr int GetOptionNum() const { return option_num_; }

 private:
    int option_num_ = 0;
    std::optional<std::string> code_path_;
};

};  // namespace fishc

#endif  // FISHC_ARGUMENT_PARSER_H_
