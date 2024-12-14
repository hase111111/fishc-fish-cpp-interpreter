
#ifndef FISHC_UTILS_H_
#define FISHC_UTILS_H_

#include <stdexcept>

namespace fishc::utils {

//! @brief Check if the given argument is an option, like "-h" or "--help".
//! @param arg The argument to check.
//! @return True if the argument is an option, false otherwise.
//! @throw std::invalid_argument If arg is nullptr.
constexpr bool IsOption(const char *arg) {
    if (arg == nullptr) {
        throw std::invalid_argument("arg is nullptr");
    }

    return arg[0] == '-';
}

//! @brief Check if the given argument is a one-character option, like "-h".
//! @param arg The argument to check.
//! @return True if the argument is a one-character option, false otherwise.
//! @throw std::invalid_argument If arg is nullptr.
constexpr bool IsOneCharOption(const char *arg) {
    if (arg == nullptr) {
        throw std::invalid_argument("arg is nullptr");
    }

    // size == 2 and arg[0] == - and arg[1] != -
    return arg[0] == '-' && arg[1] != '-' && arg[2] == '\0';
}

}  // namespace fishc::utils

#endif  // FISHC_UTILS_H_
