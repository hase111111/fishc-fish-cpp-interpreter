

#ifndef FISHC_STACK_H_
#define FISHC_STACK_H_

#include <cstddef>
#include <deque>
#include <vector>
#include <optional>

#include "type.h"

namespace fishc {

using StackPart = std::deque<Number>;
using Register = std::optional<Number>;

struct Stack final {

Stack() : default_stack(), default_register(), stacks(), registers() {}

bool operator==(const Stack& rhs) const;

[[nodiscard]] Number pop_back();
[[nodiscard]] Number pop_front();
[[nodiscard]] Number back() const;
[[nodiscard]] Number front() const;
void push_back(const Number& n);
void push_front(const Number& n);
[[nodiscard]] bool empty() const;
[[nodiscard]] size_t size() const;
void reverse();
void swap2();

bool register_has_val() const;
Number pop_register();
void push_register(const Number& n);

void push_back_stack(int num);
void pop_back_stack();

StackPart default_stack;
Register default_register;
std::vector<StackPart> stacks;
std::vector<Register> registers;

};

}  // namespace fishc

#endif  // FISHC_STACK_H_
