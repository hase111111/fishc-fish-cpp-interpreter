
#include "interpreter.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "code_box.h"
#include "exception.h"
#include "fish_resource.h"
#include "type.h"

namespace fishc {

Interpreter::Interpreter(const std::string& code, int limit, bool debug)
    : fish_resource_ptr_(std::make_shared<FishResource>(code))
    , instruction_handler_(fish_resource_ptr_) 
    , limit_(limit) 
    , debug_(debug) {
    assert(fish_resource_ptr_ != nullptr && "fish_resource_ptr_ must not be null.");
}

void Interpreter::Run() {
    while (true) {
        try {
            if (!Loop()) {
                break;
            }
        } catch (const base_fish_exception& _) {
            // If an exception is thrown,
            // print the error message and exit the program.
            // No matter what error occurs, there is only one error message.
            std::cout << "Something smells fishy..." << std::endl;
            std::cout << "Error: " << _.what() << std::endl;
            break;
        } catch (const std::exception& e) {
            std::cout << "Something smells fishy..." << std::endl;
            std::cout << "Unknown Error:" << e.what() << std::endl;
            break;
        }

        Move();

        if (limit_ > 0 && count_++ > limit_) {
            std::cout << "Something smells fishy..." << std::endl;
            std::cout << "Error: Limit exceeded." << std::endl;
            break;
        }
    }
}

bool Interpreter::Loop() {
    if (fish_resource_ptr_->skip_) {
        fish_resource_ptr_->skip_ = false;
        return true;
    }

    const Number c = fish_resource_ptr_->code_box_
        .GetChar(fish_resource_ptr_->x_, fish_resource_ptr_->y_);

    if (fish_resource_ptr_->use_double_quote_ 
        || fish_resource_ptr_->use_single_quote_) {
        if (!StringMode(c)) {
            fish_resource_ptr_->use_double_quote_ = false;
            fish_resource_ptr_->use_single_quote_ = false;
        }
        return true;
    }

    const char ch = CodeToChar(c);
    return instruction_handler_.Handle(ch);
}

void Interpreter::Move() noexcept {
    switch (fish_resource_ptr_->direction_) {
        case FishResource::Direction::kRight: {
            fish_resource_ptr_->x_++;
            break;
        }
        case FishResource::Direction::kLeft: {
            fish_resource_ptr_->x_--;
            break;
        }
        case FishResource::Direction::kUp: {
            fish_resource_ptr_->y_--;
            break;
        }
        case FishResource::Direction::kDown: {
            fish_resource_ptr_->y_++;
            break;
        }
        default: {
            assert(false && "unknown direction");
            break;
        }
    }

    // clamp x_ and y_.
    if (fish_resource_ptr_->x_ < 0) {
        fish_resource_ptr_->x_ = fish_resource_ptr_->code_box_.GetMaxWidth() - 1;
    } else if (fish_resource_ptr_->x_ >= fish_resource_ptr_->code_box_.GetMaxWidth()) {
        fish_resource_ptr_->x_ = 0;
    }

    if (fish_resource_ptr_->y_ < 0) {
        fish_resource_ptr_->y_ = fish_resource_ptr_->code_box_.GetMaxHeight() - 1;
    } else if (fish_resource_ptr_->y_ >= fish_resource_ptr_->code_box_.GetMaxHeight()) {
        fish_resource_ptr_->y_ = 0;
    }
}

bool Interpreter::StringMode(const Number code) {
    if (fish_resource_ptr_->use_double_quote_) {
        // code is " (double quote). End the string mode.
        if (code.index() == 0) {
            ImplInt i = std::get<ImplInt>(code);
            if (static_cast<char>(i) == '"') {
                return false;
            }
        } 
    }

    if (fish_resource_ptr_->use_single_quote_) {
        // code is ' (single quote). End the string mode.
        if (code.index() == 0) {
            ImplInt i = std::get<ImplInt>(code);
            if (static_cast<char>(i) == '\'') {
                return false;
            }
        }
    }

    fish_resource_ptr_->stack_.back().push_back(code);

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

}  // namespace fishc
