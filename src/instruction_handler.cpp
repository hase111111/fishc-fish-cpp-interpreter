
#include "instruction_handler.h"

#include <algorithm>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <string>

#include "exception.h"
#include "fish_resource.h"
#include "type.h"

namespace fishc {

InstructionHandler::InstructionHandler(const std::shared_ptr<FishResource> &fish_resource_ptr) noexcept
    : fish_resource_ptr_(fish_resource_ptr)
    , mt_(std::random_device{}()) {
    assert(fish_resource_ptr_ != nullptr && "fish_resource_ptr_ must not be null.");
}

bool InstructionHandler::Handle(const char ch) {
    using Dir = FishResource::Direction;

    assert(!fish_resource_ptr_->stack_.empty() && "stack must not be empty.");

    switch (ch) {
        // Movement and execution
        case '>': {
            fish_resource_ptr_->direction_ = Dir::kRight;
            return true;
        }
        case '<': {
            fish_resource_ptr_->direction_ = Dir::kLeft;
            return true;
        }
        case '^': {
            fish_resource_ptr_->direction_ = Dir::kUp;
            return true;
        }
        case 'v': {
            fish_resource_ptr_->direction_ = Dir::kDown;
            return true;
        }
        // Mirrors
        case '/': case '\\': case '|': case '_': case '#': {
            Mirror(ch);
            return true;
        }
        // Random
        case 'x': {
            std::uniform_int_distribution<int> dist(0, 3);
            int r = dist(mt_);
            fish_resource_ptr_->direction_ = static_cast<Dir>(r);
            return true;
        }
        // Trampoline
        case '!' : {
            fish_resource_ptr_->skip_ = true;
            return true;
        }
        // Conditional trampoline
        case '?' : {
            ConditionalTrampoline();
            return true;
        }
        case '.' : {
            Jump();
            return true;
        }
        // Literals and operators
        case '0': case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': {
            fish_resource_ptr_->stack_.back()
                .push_back(static_cast<ImplInt>(ch - '0'));
            return true;
        }
        case 'a':  case 'b': case 'c': case 'd': case 'e': case 'f': {
            fish_resource_ptr_->stack_.back()
                .push_back(static_cast<ImplInt>(ch - 'a' + 10));
            return true;
        }
        case '+': case '-': case '*': case ',': case '%': {
            ArithmeticOperators(ch);
            return true;
        } 
        case '=': case '(': case ')': {
            ComparisonOperator(ch);
            return true;
        }
        case '"': {
            fish_resource_ptr_->use_double_quote_ = true;
            return true;
        }
        case '\'': {
            fish_resource_ptr_->use_single_quote_ = true;
            return true;
        }
        // Stack manipulation
        case ':' : {
            if (fish_resource_ptr_->stack_.back().empty()) {
                throw stack_exception("call ':', but stack is empty.");
            }

            fish_resource_ptr_->stack_.back().push_back(fish_resource_ptr_->stack_.back().back());
            return true;
        }
        case '~' : {
            if (fish_resource_ptr_->stack_.back().empty()) {
                throw stack_exception("call '~', but stack is empty.");
            }

            fish_resource_ptr_->stack_.back().pop_back();
            return true;
        }
        case '$' : {
            if (fish_resource_ptr_->stack_.back().size() < 2) {
                throw stack_exception("call '$', but stack size is less than 2.");
            }

            Number a = fish_resource_ptr_->stack_.back().back();
            fish_resource_ptr_->stack_.back().pop_back();
            Number b = fish_resource_ptr_->stack_.back().back();
            fish_resource_ptr_->stack_.back().pop_back();

            fish_resource_ptr_->stack_.back().push_back(a);
            fish_resource_ptr_->stack_.back().push_back(b);
            return true;
        }
        case '@' : {
            if (fish_resource_ptr_->stack_.back().size() < 3) {
                throw stack_exception("call '@', but stack size is less than 3.");
            }

            const Number a = fish_resource_ptr_->stack_.back().back();
            fish_resource_ptr_->stack_.back().pop_back();
            const Number b = fish_resource_ptr_->stack_.back().back();
            fish_resource_ptr_->stack_.back().pop_back();
            const Number c = fish_resource_ptr_->stack_.back().back();
            fish_resource_ptr_->stack_.back().pop_back();

            fish_resource_ptr_->stack_.back().push_back(a);
            fish_resource_ptr_->stack_.back().push_back(c);
            fish_resource_ptr_->stack_.back().push_back(b);
            return true;
        }
        case '{' : {
            // left rotation.
            if (fish_resource_ptr_->stack_.back().empty()) {
                throw stack_exception("call '{', but stack is empty.");
            }

            const Number a = fish_resource_ptr_->stack_.back().front();
            fish_resource_ptr_->stack_.back().pop_front();
            fish_resource_ptr_->stack_.back().push_back(a);
            return true;
        }
        case '}' : {
            // right rotation.
            if (fish_resource_ptr_->stack_.back().empty()) {
                throw stack_exception("call '}', but stack is empty.");
            }

            const Number a = fish_resource_ptr_->stack_.back().back();
            fish_resource_ptr_->stack_.back().pop_back();
            fish_resource_ptr_->stack_.back().push_front(a);
            return true;
        }
        case 'r' : {
            // reverse the stack.
            std::reverse(fish_resource_ptr_->stack_.back().begin(),
                fish_resource_ptr_->stack_.back().end());
            return true;
        }
        case 'l' : {
            ImplInt i = fish_resource_ptr_->stack_.back().size();
            fish_resource_ptr_->stack_.back().push_back(static_cast<ImplInt>(i));
            return true;
        }
        // Input/output
       case 'o' : {
            if (fish_resource_ptr_->stack_.back().empty()) {
                throw stack_exception("call 'o', but stack is empty.");
            }

            if (IsInt(fish_resource_ptr_->stack_.back().back())) {
                ImplInt i = std::get<ImplInt>(fish_resource_ptr_->stack_.back().back());
                std::cout << static_cast<char>(i);
            } else {
                ImplFloat f = std::get<ImplFloat>(fish_resource_ptr_->stack_.back().back());
                std::cout << static_cast<char>(f);
            }
            fish_resource_ptr_->stack_.back().pop_back();
            return true;
        }
        case 'n': {
            if (fish_resource_ptr_->stack_.back().empty()) {
                throw stack_exception("call 'n', but stack is empty.");
            }

            std::cout << ToIntIfPossible(fish_resource_ptr_->stack_.back().back());
            fish_resource_ptr_->stack_.back().pop_back();
            return true;
        }
        case 'i': {
            char c;

            if (std::cin.get(c)) {
                fish_resource_ptr_->stack_.back().push_back(static_cast<ImplInt>(c));
            } else {
                fish_resource_ptr_->stack_.back().push_back(static_cast<ImplInt>(-1));
            }
            return true;
        }
        // Reflection/miscellaneous
        case 'g' : {
            if (fish_resource_ptr_->stack_.back().size() < 2) {
                throw stack_exception("call 'g', but stack size is less than 2.");
            }

            const Number a = ToIntIfPossible(fish_resource_ptr_->stack_.back().back());
            fish_resource_ptr_->stack_.back().pop_back();
            const Number b = ToIntIfPossible(fish_resource_ptr_->stack_.back().back());
            fish_resource_ptr_->stack_.back().pop_back();

            const auto x = GetIntOr(b, -1);
            const auto y = GetIntOr(a, -1);

            if (x < 0 || y < 0) {
                throw invalid_argument_exception("Call 'g', but x or y is negative.");
            }

            fish_resource_ptr_->stack_.back().push_back(fish_resource_ptr_->code_box_.GetChar(x, y));
            return true;
        }
        case 'p' : {
            if (fish_resource_ptr_->stack_.back().size() < 3) {
                throw stack_exception("call 'p', but stack size is less than 3.");
            }

            const Number a = ToIntIfPossible(fish_resource_ptr_->stack_.back().back());
            fish_resource_ptr_->stack_.back().pop_back();
            const Number b = ToIntIfPossible(fish_resource_ptr_->stack_.back().back());
            fish_resource_ptr_->stack_.back().pop_back();
            const Number c = ToIntIfPossible(fish_resource_ptr_->stack_.back().back());
            fish_resource_ptr_->stack_.back().pop_back();

            const ImplInt x = GetIntOr(c, -1);
            const ImplInt y = GetIntOr(b, -1);

            if (x < 0 || y < 0) {
                throw invalid_argument_exception("Call 'p', but x or y is negative.");
            }

            fish_resource_ptr_->code_box_.SetChar(x, y, a);
            return true;
        }
        case ';': {
            // exit the program.
            return false;
        }
        case ' ' :  case 0: {
            // no operation.
            return true;
        }
        case '&': {
            if (fish_resource_ptr_->register_.has_value()) {
                fish_resource_ptr_->stack_.back().push_back(fish_resource_ptr_->register_.value());
                fish_resource_ptr_->register_ = std::nullopt;
            } else {
                if (fish_resource_ptr_->stack_.back().empty()) {
                    throw stack_exception("call '&', but stack is empty.");
                }

                fish_resource_ptr_->register_ = fish_resource_ptr_->stack_.back().back();
                fish_resource_ptr_->stack_.back().pop_back();
            }
            return true;
        }
        case '[' : {
            if (fish_resource_ptr_->stack_.back().empty()) {
                throw stack_exception("call '[', but stack is empty.");
            }

            ImplInt i = GetIntOr(fish_resource_ptr_->stack_.back().back(), -1);

            if (i < 0) {
                throw invalid_argument_exception("Call '[', but i is negative.");
            }

            fish_resource_ptr_->stack_.push_back({});

            for (int j = 0; j < i; ++j) {
                Number n = fish_resource_ptr_->stack_[fish_resource_ptr_->stack_.size() - 2].back();
                fish_resource_ptr_->stack_[fish_resource_ptr_->stack_.size() - 2].pop_back();
                fish_resource_ptr_->stack_.back().push_back(n);
            }
            return true;
        }
        case ']' : {
            if (fish_resource_ptr_->stack_.size() == 1) {
                throw stack_exception("call ']', but stack size is 1.");
            }

            auto s = fish_resource_ptr_->stack_.back();
            fish_resource_ptr_->stack_.pop_back();
            
            for (const auto& n : s) {
                fish_resource_ptr_->stack_.back().push_back(n);
            }
            return true;
        }
        default: {
            std::string message = "unknown character: "
                + std::string(1, ch) + " (" + std::to_string(static_cast<int>(ch)) + ")";
            throw invalid_instruction_exception(message);
        }
    }

    return false;
}

void InstructionHandler::Mirror(const char ch) {
    using Dir = FishResource::Direction;

    switch (ch) {
        case '/': {
            if (fish_resource_ptr_->direction_ == Dir::kRight) {
                fish_resource_ptr_->direction_ = Dir::kUp;
            } else if (fish_resource_ptr_->direction_ == Dir::kLeft) {
                fish_resource_ptr_->direction_ = Dir::kDown;
            } else if (fish_resource_ptr_->direction_ == Dir::kUp) {
                fish_resource_ptr_->direction_ = Dir::kRight;
            } else if (fish_resource_ptr_->direction_ == Dir::kDown) {
                fish_resource_ptr_->direction_ = Dir::kLeft;
            }
            break;
        }
        case '\\': {
            if (fish_resource_ptr_->direction_ == Dir::kRight) {
                fish_resource_ptr_->direction_ = Dir::kDown;
            } else if (fish_resource_ptr_->direction_ == Dir::kLeft) {
                fish_resource_ptr_->direction_ = Dir::kUp;
            } else if (fish_resource_ptr_->direction_ == Dir::kUp) {
                fish_resource_ptr_->direction_ = Dir::kLeft;
            } else if (fish_resource_ptr_->direction_ == Dir::kDown) {
                fish_resource_ptr_->direction_ = Dir::kRight;
            }
            break;
        }
        case '|': {
            if (fish_resource_ptr_->direction_ == Dir::kLeft 
                || fish_resource_ptr_->direction_ == Dir::kRight) {
                fish_resource_ptr_->direction_ = 
                    (fish_resource_ptr_->direction_ == Dir::kLeft) ?
                        Dir::kRight : Dir::kLeft;
            }
            break;
        }
        case '_': {
            if (fish_resource_ptr_->direction_ == Dir::kUp 
                || fish_resource_ptr_->direction_ == Dir::kDown) {
                fish_resource_ptr_->direction_ = 
                    (fish_resource_ptr_->direction_ == Dir::kUp) ? 
                        Dir::kDown : Dir::kUp;
            }
            break;
        }
        case '#': {
            if (fish_resource_ptr_->direction_ == Dir::kRight) {
                fish_resource_ptr_->direction_ = Dir::kLeft;
            } else if (fish_resource_ptr_->direction_ == Dir::kLeft) {
                fish_resource_ptr_->direction_ = Dir::kRight;
            } else if (fish_resource_ptr_->direction_ == Dir::kUp) {
                fish_resource_ptr_->direction_ = Dir::kDown;
            } else if (fish_resource_ptr_->direction_ == Dir::kDown) {
                fish_resource_ptr_->direction_ = Dir::kUp;
            }
            break;
        }
        default: {
            assert(false && "unknown character");
        }
    }
}

void InstructionHandler::ConditionalTrampoline() {
    if (fish_resource_ptr_->stack_.back().empty()) {
        throw stack_exception("call '?', but stack is empty.");
    }

    Number a = fish_resource_ptr_->stack_.back().back();
    fish_resource_ptr_->stack_.back().pop_back();

    if (IsInt(a)) {
        ImplInt i = std::get<ImplInt>(a);
        if (i == 0) {
            fish_resource_ptr_->skip_ = true;
        }
    } else {
        ImplFloat f = std::get<ImplFloat>(a);
        if (f == 0.0) {
            fish_resource_ptr_->skip_ = true;
        }
    }
}

void InstructionHandler::Jump() {
    if (fish_resource_ptr_->stack_.back().empty()) {
        throw stack_exception("call '.', but stack is empty.");
    }

    Number a = ToIntIfPossible(fish_resource_ptr_->stack_.back().back());
    fish_resource_ptr_->stack_.back().pop_back();
    Number b = ToIntIfPossible(fish_resource_ptr_->stack_.back().back());
    fish_resource_ptr_->stack_.back().pop_back();

    fish_resource_ptr_->x_ = GetIntOr(b, -1);
    fish_resource_ptr_->y_ = GetIntOr(a, -1);

    if (fish_resource_ptr_->x_ < 0 || fish_resource_ptr_->y_ < 0) {
        std::string message = "Call '.', but x or y is negative. x: " 
            + std::to_string(fish_resource_ptr_->x_) + ", y: " 
            + std::to_string(fish_resource_ptr_->y_);
        throw invalid_argument_exception(message);
    }
}

void InstructionHandler::ArithmeticOperators(const char op) {
    if (fish_resource_ptr_->stack_.back().size() < 2) {
        throw stack_exception("Call arithmetic operators, "
            "but stack size is less than 2.");
    }

    const Number a = fish_resource_ptr_->stack_.back().back();
    fish_resource_ptr_->stack_.back().pop_back();
    const Number b = fish_resource_ptr_->stack_.back().back();
    fish_resource_ptr_->stack_.back().pop_back();

    switch (op) {
        case '+': {
            fish_resource_ptr_->stack_.back().push_back(a + b);
            break;
        }
        case '-': {
            fish_resource_ptr_->stack_.back().push_back(b - a);
            break;
        }
        case '*': {
            fish_resource_ptr_->stack_.back().push_back(a * b);
            break;
        }
        case ',': {
            fish_resource_ptr_->stack_.back().push_back(b / a);
            break;
        }
        case '%': {
            fish_resource_ptr_->stack_.back().push_back(b % a);
            break;
        }
        default: {
            assert(false && "unknown character");
        }
    }
}

void InstructionHandler::ComparisonOperator(const char op) {
    if (fish_resource_ptr_->stack_.back().size() < 2) {
        throw stack_exception("Call comparison operators, "
            "but stack size is less than 2.");
    }

    const Number a = fish_resource_ptr_->stack_.back().back();
    fish_resource_ptr_->stack_.back().pop_back();
    const Number b = fish_resource_ptr_->stack_.back().back();
    fish_resource_ptr_->stack_.back().pop_back();

    switch (op) {
        case '=' : {
            fish_resource_ptr_->stack_.back().push_back(a == b ?
                static_cast<ImplInt>(1) : static_cast<ImplInt>(0));
            break;
        }
        case '(' : {
            fish_resource_ptr_->stack_.back().push_back(a > b ?
                static_cast<ImplInt>(1) : static_cast<ImplInt>(0));
            break;
        }
        case ')' : {
            fish_resource_ptr_->stack_.back().push_back(a < b ?
                static_cast<ImplInt>(1) : static_cast<ImplInt>(0));
            break;
        }
        default: {
            assert(false && "unknown character");
        }
    }
}

}  // namespace fishc
