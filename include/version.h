
// Copyright (c) 2024-2025 T.Hasegawa
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php

#ifndef FISHC_VERSION_H_
#define FISHC_VERSION_H_

#include <string>

namespace fishc {

const std::string kProgramName = "fishc";
const std::string kVersion = "0.1.0";

class VersionPrinter final {
  public:
    VersionPrinter() noexcept = default;
    ~VersionPrinter() = default;

    void Print() const noexcept;
};

}  // namespace fishc

#endif  // FISHC_VERSION_H_
