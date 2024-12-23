
#ifndef FISHC_FISH_RESOURCE_H_
#define FISHC_FISH_RESOURCE_H_

#include "code_box.h"
#include "type.h"

namespace fishc {

struct FishResource final {
    enum class Direction : int {
        kRight,
        kLeft,
        kUp,
        kDown,
    };

    FishResource() = delete;
    explicit FishResource(const std::string& code) : code_box_(code) {
        stack_.push_back(std::deque<Number>());
    }

    CodeBox code_box_;
    Stack stack_;
    Register register_{std::nullopt};
    int x_{0}, y_{0};
    Direction direction_{Direction::kRight};
    bool skip_{false};
    bool use_double_quote_{false};
    bool use_single_quote_{false};
};

}  // namespace fishc

#endif  // FISHC_FISH_RESOURCE_H_
