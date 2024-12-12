
#ifndef FISHC_TYPE_H_
#define FISHC_TYPE_H_

#include <deque>
#include <variant>

namespace fishc {

using ImplInt = long long;
using ImplFloat = double;
using Number = std::variant<ImplInt, ImplFloat>;
using Stack = std::deque<Number>;

}  // namespace fishc

#endif  // FISHC_TYPE_H_
