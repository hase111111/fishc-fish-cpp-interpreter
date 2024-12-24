
// Copyright (c) 2024-2025 T.Hasegawa
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php

#ifndef FISHC_INTERPRETER_H_
#define FISHC_INTERPRETER_H_

#include <memory>
#include <string>

#include "fish_resource.h"
#include "instruction_handler.h"
#include "type.h"

namespace fishc {

class Interpreter final {
  public:
    Interpreter() = delete;
    Interpreter(const std::string& code, int limit);
    ~Interpreter() = default;

    void Run();

  private:
    bool Loop();  //!< Return true if the loop should continue.
    void Move() noexcept;
    [[nodiscard]] char CodeToChar(Number code) const;

    //! Return true if the string mode should continue.
    bool StringMode(Number code);

    const std::shared_ptr<FishResource> fish_resource_ptr_;
    InstructionHandler instruction_handler_;
    const int limit_;
    int count_ = 0;
};

}  // namespace fishc

#endif  // FISHC_INTERPRETER_H_
