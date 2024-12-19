
#ifndef FISHC_TYPE_H_
#define FISHC_TYPE_H_

#include <cassert>
#include <deque>
#include <optional>
#include <variant>

namespace fishc {

using ImplInt = long long;
using ImplFloat = double;
using Number = std::variant<ImplInt, ImplFloat>;
using Stack = std::deque<Number>;
using Register = std::optional<Number>;

inline bool IsInt(const Number& n) noexcept {
    return n.index() == 0;
}

inline bool IsFloat(const Number& n) noexcept {
    return n.index() == 1;
}

[[nodiscard]] inline ImplInt GetIntOr(
    const Number& n, const ImplInt default_v) noexcept {
    if (IsInt(n)) {
        return std::get<ImplInt>(n);
    }
    return default_v;
}

[[nodiscard]] inline ImplFloat GetFloatOr(
    const Number& n, const ImplFloat default_v) noexcept {
    if (IsFloat(n)) {
        return std::get<ImplFloat>(n);
    }
    return default_v;
}

[[nodiscard]]
inline Number ToIntIfPossible(const Number& n) noexcept {
    if (IsInt(n)) {
        return n;
    }
    return static_cast<ImplInt>(std::get<ImplFloat>(n));
}

[[nodiscard]] Number operator+(const Number& a, const Number& b) noexcept;

[[nodiscard]] Number operator-(const Number& a, const Number& b) noexcept;

[[nodiscard]] Number operator*(const Number& a, const Number& b) noexcept;

[[nodiscard]] Number operator/(const Number& a, const Number& b);

[[nodiscard]] Number operator%(const Number& a, const Number& b);

}  // namespace fishc

#endif  // FISHC_TYPE_H_
