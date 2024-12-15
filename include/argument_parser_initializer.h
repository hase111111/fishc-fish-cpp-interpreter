
#ifndef FISHC_ARGUMENT_PARSER_INITIALIZER_H_
#define FISHC_ARGUMENT_PARSER_INITIALIZER_H_

#include "argument_parser.h"

namespace fishc {

class ArgumentParserInitializer final {
  public:
    ArgumentParserInitializer() = default;
    ~ArgumentParserInitializer() = default;

    [[nodiscard]] ArgumentParser Initialize() const noexcept;
};

}  // namespace fishc

#endif  // FISHC_ARGUMENT_PARSER_INITIALIZER_H_
