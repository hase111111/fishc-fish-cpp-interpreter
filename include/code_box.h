
// Copyright (c) 2024-2025 T.Hasegawa
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php

#ifndef FIHSC_CODE_BOX_H_
#define FIHSC_CODE_BOX_H_

#include <cassert>
#include <string>
#include <vector>

#include "type.h"

namespace fishc {

class CodeBox final {
  public:
    CodeBox() = delete;
    CodeBox(const std::string& code);
    ~CodeBox() = default;

    inline int GetMaxWidth() const noexcept { return max_width_; }
    inline int GetMaxHeight() const noexcept { return max_height_; }

    inline Number GetChar(const int x, const int y) const noexcept {
        if (x < 0 || x >= max_width_ || y < 0 || y >= max_height_) {
            return default_char_;
        }
        return code_box_[y][x]; 
    }
    void SetChar(int x, int y, Number c);

    std::string DebugString() const;

  private:
    void ReserveCodeBox(int width, int height);

    std::vector<std::vector<Number>> code_box_;

    int max_width_{0};
    int max_height_{0};
    const Number default_char_{static_cast<ImplInt>(0)};
};

}  // namespace fihsc

#endif  // FIHSC_CODE_BOX_H_
