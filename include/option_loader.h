
#ifndef FISHC_OPTION_LOADER_H_
#define FISHC_OPTION_LOADER_H_

#include <string>

namespace fishc {

class OptionLoader final {
  public:
    OptionLoader() = default;

    void Load(int argc, char *argv[]);
    constexpr int GetOptionNum() const { return option_num_; }

 private:
    int option_num_ = 0;
};

};  // namespace fishc

#endif // FISHC_OPTION_LOADER_H_
