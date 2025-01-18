
#include "stack.h"

#include <algorithm>

#include "exception.h"

namespace fishc {

bool Stack::operator==(const Stack& rhs) const {
    if (default_stack != rhs.default_stack) {
        return false;
    }

    if (default_register != rhs.default_register) {
        return false;
    }

    if (stacks != rhs.stacks) {
        return false;
    }

    if (registers != rhs.registers) {
        return false;
    }

    return true;
}

Number Stack::pop_back() {
    if (stacks.empty()) {
        // get val from default stack
        if (default_stack.empty()) {
            throw stack_exception("Stack is empty");
        }

        const auto val = default_stack.back();
        default_stack.pop_back();
        return val;
    } else {
        // get val from stack
        if (stacks.back().empty()) {
            throw stack_exception("Stack is empty");
        }

        const auto val = stacks.back().back();
        stacks.back().pop_back();
        return val;
    }
}

Number Stack::pop_front() {
    if (stacks.empty()) {
        // get val from default stack
        if (default_stack.empty()) {
            throw stack_exception("Stack is empty");
        }

        const auto val = default_stack.front();
        default_stack.pop_front();
        return val;
    } else {
        // get val from stack
        if (stacks.back().empty()) {
            throw stack_exception("Stack is empty");
        }

        const auto val = stacks.back().front();
        stacks.back().pop_front();
        return val;
    }
}

Number Stack::back() const {
    if (stacks.empty()) {
        // get val from default stack
        if (default_stack.empty()) {
            throw stack_exception("Stack is empty");
        }

        return default_stack.back();
    } else {
        // get val from stack
        if (stacks.back().empty()) {
            throw stack_exception("Stack is empty");
        }

        return stacks.back().back();
    }
}

Number Stack::front() const {
    if (stacks.empty()) {
        // get val from default stack
        if (default_stack.empty()) {
            throw stack_exception("Stack is empty");
        }

        return default_stack.front();
    } else {
        // get val from stack
        if (stacks.back().empty()) {
            throw stack_exception("Stack is empty");
        }

        return stacks.back().front();
    }
}

void Stack::push_back(const Number& n) {
    if (stacks.empty()) {
        // push val to default stack
        default_stack.push_back(n);
    } else {
        // push val to stack
        stacks.back().push_back(n);
    }
}

void Stack::push_front(const Number& n) {
    if (stacks.empty()) {
        // push val to default stack
        default_stack.push_front(n);
    } else {
        // push val to stack
        stacks.back().push_front(n);
    }
}

bool Stack::empty() const {
    if (stacks.empty()) {
        return default_stack.empty();
    } else {
        return stacks.back().empty();
    }
}

size_t Stack::size() const {
    if (stacks.empty()) {
        return default_stack.size();
    } else {
        return stacks.back().size();
    }
}

void Stack::reverse() {
    if (stacks.empty()) {
        std::reverse(default_stack.begin(), default_stack.end());
    } else {
        std::reverse(stacks.back().begin(), stacks.back().end());
    }
}

bool Stack::register_has_val() const {
    if (registers.empty()) {
        return default_register.has_value();
    } else {
        return registers.back().has_value();
    }
}

Number Stack::pop_register() {
    if (registers.empty()) {
        if (!default_register.has_value()) {
            throw stack_exception("Register is empty");
        }

        const auto val = default_register.value();
        default_register.reset();
        return val;
    } else {
        if (!registers.back().has_value()) {
            throw stack_exception("Register is empty");
        }

        const auto val = registers.back().value();
        registers.back().reset();
        return val;
    }
}

void Stack::push_register(const Number& n) {
    if (registers.empty()) {
        default_register = n;
    } else {
        registers.back() = n;
    }
}

void Stack::push_back_stack(int num) {
    // get number in now stack
    StackPart new_stack;

    if (stacks.empty()) {
        for (int i = 0; i < num; ++i) {
            new_stack.push_back(default_stack.back());
            default_stack.pop_back();
        }
    } else {
        for (int i = 0; i < num; ++i) {
            new_stack.push_back(stacks.back().back());
            stacks.back().pop_back();
        }
    }

    std::sort(new_stack.begin(), new_stack.end());

    stacks.push_back(new_stack);
}

void Stack::pop_back_stack() {
    if (stacks.empty()) {
        throw stack_exception("Stack is empty");
    }

    StackPart now_stack = stacks.back();
    stacks.pop_back();
    if (stacks.empty()) {
        default_stack.insert(default_stack.end(), now_stack.begin(), now_stack.end());
    } else {
        stacks.back().insert(stacks.back().end(), now_stack.begin(), now_stack.end());
    }
}

}  // namespace fishc
