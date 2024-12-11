
#ifndef FISHC_INTERPRETER_H_
#define FISHC_INTERPRETER_H_

#include <deque>
#include <string>
#include <variant>

namespace fishc {

class Interpreter final {
    using fish_stack = std::deque<std::variant<int, float>>;

  public:
    Interpreter() = delete;
    Interpreter(const std::string& code);
    ~Interpreter() = default;

    void Run();

  private:
};

}  // namespace fishc

#endif  // FISHC_INTERPRETER_H_
