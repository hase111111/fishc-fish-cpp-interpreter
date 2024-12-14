
#ifndef FISHC_INTERPRETER_H_
#define FISHC_INTERPRETER_H_

#include <string>

#include "code_box.h"
#include "type.h"

namespace fishc {

class Interpreter final {
    enum class Direction {
        kRight,
        kLeft,
        kUp,
        kDown,
    };
    
  public:
    Interpreter() = delete;
    Interpreter(const std::string& code);
    ~Interpreter() = default;

    void Run();

  private:
    bool Loop();  //!< Return true if the loop should continue.
    void Move();
    bool StringMode(Number code);  //!< Return true if the string mode should continue.

    CodeBox code_box_;
    Stack stack_;
    Register register_;
    int x_{0}, y_{0};
    Direction direction_{Direction::kRight};
    bool skip_{false};
    bool use_double_quote_{false};
    bool use_single_quote_{false};
};

}  // namespace fishc

#endif  // FISHC_INTERPRETER_H_
