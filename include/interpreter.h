
#ifndef FISHC_INTERPRETER_H_
#define FISHC_INTERPRETER_H_

#include <deque>
#include <string>

namespace fishc {

class Interpreter final {
  public:
    Interpreter() = delete;
    Interpreter(const std::string& code);
    ~Interpreter() = default;

    void Run();

  private:
};

}  // namespace fishc

#endif  // FISHC_INTERPRETER_H_
