
#include <iostream>

#include "interperter.h"

namespace fishc {

Interpreter::Interpreter(const std::string& code) : code_(code) {}

void Interpreter::Run() {
    std::cout << "Running code: " << code_ << std::endl;
}

}  // namespace fishc
