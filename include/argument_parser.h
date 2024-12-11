
#ifndef FISHC_ARGUMENT_PARSER_H_
#define FISHC_ARGUMENT_PARSER_H_

#include <string>

namespace fishc {

class ArgumentParser final {
  public:
    ArgumentParser() = default;

    void Load(int argc, char *argv[]);
    constexpr int GetOptionNum() const { return option_num_; }

 private:
    int option_num_ = 0;
};

};  // namespace fishc

#endif  // FISHC_ARGUMENT_PARSER_H_
