
#ifndef FISHC_TYPE_H_
#define FISHC_TYPE_H_

#include <deque>
#include <optional>
#include <variant>

namespace fishc {

using ImplInt = long long;
using ImplFloat = double;
using Number = std::variant<ImplInt, ImplFloat>;
using Stack = std::deque<Number>;
using Register = std::optional<Number>;

Number operator+(const Number& a, const Number& b);
Number operator-(const Number& a, const Number& b);
Number operator*(const Number& a, const Number& b);

}  // namespace fishc

#endif  // FISHC_TYPE_H_
