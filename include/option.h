
// Copyright (c) 2024-2025 T.Hasegawa
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php

#ifndef FISHC_OPTION_H_
#define FISHC_OPTION_H_

#include <string>

namespace fishc {

enum class OptionMode : int {
    kHelp = 0,
    kVersion,
    kCode,
    kStack,
    kValue,
    kTick,
    kAlwaysTick,
    kFile,
    kUnknown
};

OptionMode ArgToOptionMode(const std::string& arg);

bool IsOption(const std::string& arg);

struct Option final {
    bool is_help_mode{false};
    bool is_version_mode{false};
    std::string code;
    std::string initial_stack;
    std::string initial_value;
    int tick{0};
    bool always_tick{false};
};


}  // namespace fishc

#endif  // FISHC_OPTION_H_
