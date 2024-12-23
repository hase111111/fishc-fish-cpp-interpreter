
// Copyright (c) 2024-2025 T.Hasegawa
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php

#ifndef FISHC_ARGUMENT_INITIALIZER_H_
#define FISHC_ARGUMENT_INITIALIZER_H_

#include <vector>

#include "argument.h"


namespace fishc {

class ArgumentInitializer final {
  public:
    ArgumentInitializer() noexcept = default;
    ~ArgumentInitializer() = default;

    [[nodiscard]] std::vector<Argument> Initialize() const noexcept;
};

}  // namespace fishc

#endif  // FISHC_ARGUMENT_INITIALIZER_H_
