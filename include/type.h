
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

[[nodiscard]] Number operator+(const Number& a, const Number& b) noexcept;

[[nodiscard]] Number operator-(const Number& a, const Number& b) noexcept;

[[nodiscard]] Number operator*(const Number& a, const Number& b) noexcept;

[[nodiscard]] Number operator/(const Number& a, const Number& b);

[[nodiscard]] Number operator%(const Number& a, const Number& b);

}  // namespace fishc

#endif  // FISHC_TYPE_H_
