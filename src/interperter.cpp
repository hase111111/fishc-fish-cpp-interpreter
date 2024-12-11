
#include "interperter.h"

#include <iostream>

#include "code_box.h"

namespace fishc {

Interpreter::Interpreter(const std::string& code) {
    CodeBox code_box(code);
    std::cout << code_box.DebugString() << std::endl;
}

void Interpreter::Run() {
}

}  // namespace fishc
