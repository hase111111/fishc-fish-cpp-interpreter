
// Copyright (c) 2024-2025 T.Hasegawa
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php

#ifndef FISHC_UTILS_H_
#define FISHC_UTILS_H_

#include <cassert>
#include <string>
#include <sstream>
#include <vector>

namespace fishc::utils {

//! @brief Check if the given argument is an option, like "-h" or "--help".
//! @param arg The argument to check.
//! @return True if the argument is an option, false otherwise.
[[nodiscard]]
inline bool IsOption(const std::string &arg) noexcept {
    assert(!arg.empty() && "arg must not be empty");
    return arg[0] == '-';
}

template<typename T>
[[nodiscard]] T StringTo(const std::string &str) {
    T value;
    std::stringstream ss(str);
    ss >> value;
    return value;
}

//! @brief Convert the given argument array to a vector of strings.
//! @param argc The number of arguments.
//! @param argv The argument array. Array length must be argc.
//! @return A vector of strings.
[[nodiscard]]
inline std::vector<std::string> ArgArrayToVector(
    const int argc, char **argv) noexcept {
    assert(argc >= 0 && "argc must be non-negative");
    assert(argv != nullptr && "argv must not be null");

    std::vector<std::string> args;

    for (int i = 0; i < argc; ++i) {
        args.push_back(argv[i]);
    }

    return args;
}

}  // namespace fishc::utils

#endif  // FISHC_UTILS_H_
