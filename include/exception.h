
#ifndef FISHC_EXCEPTION_H_
#define FISHC_EXCEPTION_H_

#include <stdexcept>

namespace fishc {

// std::runtime_error を継承する
class base_fish_exception : public std::runtime_error {
  public:
    explicit base_fish_exception(const std::string &what_arg) : std::runtime_error(what_arg) {}
    explicit base_fish_exception(const char *what_arg) : std::runtime_error(what_arg) {}
};

// スタック操作時の例外
class stack_exception : public base_fish_exception {
  public:
    explicit stack_exception(const std::string &what_arg) : base_fish_exception(what_arg) {}
    explicit stack_exception(const char *what_arg) : base_fish_exception(what_arg) {}
};

// 無向な命令の例外
class invalid_instruction_exception : public base_fish_exception {
  public:
    explicit invalid_instruction_exception(const std::string &what_arg) : base_fish_exception(what_arg) {}
    explicit invalid_instruction_exception(const char *what_arg) : base_fish_exception(what_arg) {}
};

// 引数が不正な場合の例外
class invalid_argument_exception : public base_fish_exception {
  public:
    explicit invalid_argument_exception(const std::string &what_arg) : base_fish_exception(what_arg) {}
    explicit invalid_argument_exception(const char *what_arg) : base_fish_exception(what_arg) {}
};

}  // namespace fishc

#endif  // FISHC_EXCEPTION_H_
