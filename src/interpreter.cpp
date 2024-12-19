
#include "interpreter.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>

#include "code_box.h"
#include "type.h"

namespace fishc {

Interpreter::Interpreter(const std::string& code) 
    : code_box_(code)
    , mt_(std::random_device{}()) {
    assert(register_.has_value() == false);
}

void Interpreter::Run() {
    while (true) {
        try {
            if (!Loop()) {
                break;
            }
        } catch (const std::exception& _) {
            // If an exception is thrown,
            // print the error message and exit the program.
            // No matter what error occurs, there is only one error message.
            std::cout << "Something smells fishy..." << std::endl;
            std::cout << "Error: " << _.what() << std::endl;
            break;
        }

        Move();
    }
}

bool Interpreter::Loop() {
    if (skip_) {
        skip_ = false;
        return true;
    }

    Number c = code_box_.GetChar(x_, y_);

    if (use_double_quote_ || use_single_quote_) {
        if (!StringMode(c)) {
            use_double_quote_ = false;
            use_single_quote_ = false;
        }
        return true;
    }

    const char ch = CodeToChar(c);
    return HandleInstruction(ch);
}

void Interpreter::Move() {
    switch (direction_) {
        case Direction::kRight: {
            x_++;
            break;
        }
        case Direction::kLeft: {
            x_--;
            break;
        }
        case Direction::kUp: {
            y_--;
            break;
        }
        case Direction::kDown: {
            y_++;
            break;
        }
        default: {
            assert(false);
            break;
        }
    }

    // clamp x_ and y_.
    if (x_ < 0) {
        x_ = code_box_.GetMaxWidth() - 1;
    } else if (x_ >= code_box_.GetMaxWidth()) {
        x_ = 0;
    }

    if (y_ < 0) {
        y_ = code_box_.GetMaxHeight() - 1;
    } else if (y_ >= code_box_.GetMaxHeight()) {
        y_ = 0;
    }
}

bool Interpreter::StringMode(const Number code) {
    if (use_double_quote_) {
        // code is " (double quote). End the string mode.
        if (code.index() == 0) {
            ImplInt i = std::get<ImplInt>(code);
            if (static_cast<char>(i) == '"') {
                return false;
            }
        } 
    }

    if (use_single_quote_) {
        // code is ' (single quote). End the string mode.
        if (code.index() == 0) {
            ImplInt i = std::get<ImplInt>(code);
            if (static_cast<char>(i) == '\'') {
                return false;
            }
        }
    }

    stack_.push_back(code);

    return true;
}

char Interpreter::CodeToChar(const Number code) const {
    // If c is float, throw an error.
    if (!IsInt(code) && !IsInt(ToIntIfPossible(code))) {
        throw std::runtime_error("Interpreter::CodeToChar: c is float.");
    }

    const ImplInt i = GetIntOr(code, 0);

    // Cast i to char. If i is not in the range of char, throw an error.
    if (i < 0 || i > 0xff) {
        throw std::runtime_error("Interpreter::CodeToChar: i is not in the range of char.");
    }

    return static_cast<char>(i);
}

bool Interpreter::HandleInstruction(const char ch) {
    switch (ch) {
        // Movement and execution
        case '>': {
            direction_ = Direction::kRight;
            break;
        }
        case '<': {
            direction_ = Direction::kLeft;
            break;
        }
        case '^': {
            direction_ = Direction::kUp;
            break;
        }
        case 'v': {
            direction_ = Direction::kDown;
            break;
        }
        // Mirrors
        case '/': {
            if (direction_ == Direction::kRight) {
                direction_ = Direction::kUp;
            } else if (direction_ == Direction::kLeft) {
                direction_ = Direction::kDown;
            } else if (direction_ == Direction::kUp) {
                direction_ = Direction::kRight;
            } else if (direction_ == Direction::kDown) {
                direction_ = Direction::kLeft;
            }
            break;
        }
        case '\\': {
            if (direction_ == Direction::kRight) {
                direction_ = Direction::kDown;
            } else if (direction_ == Direction::kLeft) {
                direction_ = Direction::kUp;
            } else if (direction_ == Direction::kUp) {
                direction_ = Direction::kLeft;
            } else if (direction_ == Direction::kDown) {
                direction_ = Direction::kRight;
            }
            break;
        }
        case '|': {
            if (direction_ == Direction::kLeft || direction_ == Direction::kRight) {
                direction_ = (direction_ == Direction::kLeft) ? Direction::kRight : Direction::kLeft;
            }
            break;
        }
        case '_': {
            if (direction_ == Direction::kUp || direction_ == Direction::kDown) {
                direction_ = (direction_ == Direction::kUp) ? Direction::kDown : Direction::kUp;
            }
            break;
        }
        case '#': {
            if (direction_ == Direction::kRight) {
                direction_ = Direction::kLeft;
            } else if (direction_ == Direction::kLeft) {
                direction_ = Direction::kRight;
            } else if (direction_ == Direction::kUp) {
                direction_ = Direction::kDown;
            } else if (direction_ == Direction::kDown) {
                direction_ = Direction::kUp;
            }
            break;
        }
        // Random
        case 'x': {
            std::uniform_int_distribution<int> dist(0, 3);
            int r = dist(mt_);
            direction_ = static_cast<Direction>(r);
            break;
        }
        // Trampoline
        case '!' : {
            skip_ = true;
            break;
        }
        // Conditional trampoline
        case '?' : {
            if (stack_.empty()) {
                throw std::runtime_error("Interpreter::Loop: stack is empty.");
            }

            Number a = stack_.back();
            stack_.pop_back();

            if (IsInt(a)) {
                ImplInt i = std::get<ImplInt>(a);
                if (i == 0) {
                    skip_ = true;
                }
            } else {
                ImplFloat f = std::get<ImplFloat>(a);
                if (f == 0.0) {
                    skip_ = true;
                }
            }
            break;
        }
        case '.' : {
            if (stack_.size() < 2) {
                throw std::runtime_error("stack size is less than 2.");
            }

            Number a = ToIntIfPossible(stack_.back());
            stack_.pop_back();
            Number b = ToIntIfPossible(stack_.back());
            stack_.pop_back();

            x_ = GetIntOr(b, -1);
            y_ = GetIntOr(a, -1);

            if (x_ < 0 || y_ < 0) {
                throw std::runtime_error("Interpreter::Loop: x or y is negative.");
            }

            break;
        }
        // Literals and operators
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
            stack_.push_back(static_cast<ImplInt>(ch - '0'));
            break;
        }
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f': {
            stack_.push_back(static_cast<ImplInt>(ch - 'a' + 10));
            break;
        }
        case '+' : {
            if (stack_.size() < 2) {
                throw std::runtime_error("stack size is less than 2.");
            }

            Number a = stack_.back();
            stack_.pop_back();
            Number b = stack_.back();
            stack_.pop_back();

            stack_.push_back(a + b);
            break;
        }
        case '-' : {
            if (stack_.size() < 2) {
                throw std::runtime_error("Interpreter::Loop: stack size is less than 2.");
            }

            Number a = stack_.back();
            stack_.pop_back();
            Number b = stack_.back();
            stack_.pop_back();

            stack_.push_back(b - a);
            break;
        }
        case '*' : {
            if (stack_.size() < 2) {
                throw std::runtime_error("Interpreter::Loop: stack size is less than 2.");
            }

            Number a = stack_.back();
            stack_.pop_back();
            Number b = stack_.back();
            stack_.pop_back();

            stack_.push_back(a * b);
            break;
        }
        case ',' : {
            if (stack_.size() < 2) {
                throw std::runtime_error("Interpreter::Loop: stack size is less than 2.");
            }

            Number a = stack_.back();
            stack_.pop_back();
            Number b = stack_.back();
            stack_.pop_back();

            stack_.push_back(b / a);
            break;
        }
        case '%' : {
            if (stack_.size() < 2) {
                throw std::runtime_error("Interpreter::Loop: stack size is less than 2.");
            }

            Number a = stack_.back();
            stack_.pop_back();
            Number b = stack_.back();
            stack_.pop_back();

            stack_.push_back(b % a);
            break;
        }
        case '=' : {
            if (stack_.size() < 2) {
                throw std::runtime_error("Interpreter::Loop: stack size is less than 2.");
            }

            Number a = stack_.back();
            stack_.pop_back();
            Number b = stack_.back();
            stack_.pop_back();

            stack_.push_back(a == b ?
                static_cast<ImplInt>(1) : static_cast<ImplInt>(0));
            break;
        }
        case '(' : {
            if (stack_.size() < 2) {
                throw std::runtime_error("Interpreter::Loop: stack size is less than 2.");
            }

            Number a = stack_.back();
            stack_.pop_back();
            Number b = stack_.back();
            stack_.pop_back();

            stack_.push_back(a > b ?
                static_cast<ImplInt>(1) : static_cast<ImplInt>(0));
            break;
        }
        case ')' : {
            if (stack_.size() < 2) {
                throw std::runtime_error("Interpreter::Loop: stack size is less than 2.");
            }

            Number a = stack_.back();
            stack_.pop_back();
            Number b = stack_.back();
            stack_.pop_back();

            stack_.push_back(a < b ?
                static_cast<ImplInt>(1) : static_cast<ImplInt>(0));
            break;
        }
        case '"': {
            use_double_quote_ = true;
            break;
        }
        case '\'': {
            use_single_quote_ = true;
            break;
        }
        // Stack manipulation
        case ':' : {
            if (stack_.empty()) {
                throw std::runtime_error("Interpreter::Loop: stack is empty.");
            }

            stack_.push_back(stack_.back());
            break;
        }
        case '~' : {
            if (stack_.empty()) {
                throw std::runtime_error("Interpreter::Loop: stack is empty.");
            }

            stack_.pop_back();
            break;
        }
        case '$' : {
            if (stack_.size() < 2) {
                throw std::runtime_error("Interpreter::Loop: stack size is less than 2.");
            }

            Number a = stack_.back();
            stack_.pop_back();
            Number b = stack_.back();
            stack_.pop_back();

            stack_.push_back(a);
            stack_.push_back(b);
            break;
        }
        case '@' : {
            if (stack_.size() < 3) {
                throw std::runtime_error("Interpreter::Loop: stack size is less than 3.");
            }

            Number a = stack_.back();
            stack_.pop_back();
            Number b = stack_.back();
            stack_.pop_back();
            Number c = stack_.back();
            stack_.pop_back();

            stack_.push_back(a);
            stack_.push_back(c);
            stack_.push_back(b);
            break;
        }
        case '{' : {
            // left rotation
            if (stack_.empty()) {
                throw std::runtime_error("Interpreter::Loop: stack is empty.");
            }

            Number a = stack_.front();
            stack_.pop_front();
            stack_.push_back(a);
            break;
        }
        case '}' : {
            // right rotation
            if (stack_.empty()) {
                throw std::runtime_error("Interpreter::Loop: stack is empty.");
            }

            Number a = stack_.back();
            stack_.pop_back();
            stack_.push_front(a);
            break;
        }
        // Input/output
       case 'o' : {
            if (stack_.empty()) {
                throw std::runtime_error("Interpreter::Loop: stack is empty.");
            }

            if (IsInt(stack_.back())) {
                ImplInt i = std::get<ImplInt>(stack_.back());
                std::cout << static_cast<char>(i);
            } else {
                ImplFloat f = std::get<ImplFloat>(stack_.back());
                std::cout << static_cast<char>(f);
            }
            stack_.pop_back();
            break;
        }
        case 'n': {
            if (stack_.empty()) {
                throw std::runtime_error("Interpreter::Loop: stack is empty.");
            }

            if (IsInt(stack_.back())) {
                ImplInt i = std::get<ImplInt>(stack_.back());
                std::cout << i;
            } else {
                ImplFloat f = std::get<ImplFloat>(stack_.back());
                std::cout << f;
            }
            stack_.pop_back();
            break;
        }
        case 'i': {
            char c;
            if (std::cin.get(c)) {
                stack_.push_back(static_cast<ImplInt>(c));
            } else {
                stack_.push_back(static_cast<ImplInt>(-1));
            }
            break;
        }
        case 'r' : {
            // reverse the stack.
            std::reverse(stack_.begin(), stack_.end());
            break;
        }
        case 'l' : {
            ImplInt i = stack_.size();
            stack_.push_back(static_cast<ImplInt>(i));
            break;
        }
        case ' ' : 
        case 0: {
            break;
        }
        // Reflection/miscellaneous
        case 'g' : {
            if (stack_.size() < 2) {
                throw std::runtime_error("Interpreter::Loop: stack size is less than 2.");
            }

            const ImplInt a = GetIntOr(stack_.back(), -1);
            stack_.pop_back();
            const ImplInt b = GetIntOr(stack_.back(), -1);
            stack_.pop_back();

            if (a < 0 || b < 0) {
                throw std::runtime_error("Interpreter::Loop: a or b is negative.");
            }

            stack_.push_back(code_box_.GetChar(b, a));
            break;
        }
        case 'p' : {
            if (stack_.size() < 3) {
                throw std::runtime_error("Interpreter::Loop: stack size is less than 3.");
            }

            const Number a = stack_.back();
            stack_.pop_back();
            const Number b = stack_.back();
            stack_.pop_back();
            const Number c = stack_.back();
            stack_.pop_back();

            const ImplInt x = GetIntOr(c, -1);
            const ImplInt y = GetIntOr(b, -1);

            if (x < 0 || y < 0) {
                throw std::runtime_error("Interpreter::Loop: x or y is negative.");
            }

            code_box_.SetChar(x, y, a);
            break;
        }
        case ';': {
            return false;
            break;
        }
        default: {
            std::string char_str = std::string(1, ch);
            throw std::runtime_error("unknown character: " + char_str);
            break;
        }
    }

    return true;
}

}  // namespace fishc
