
#ifndef FISHC_VERSION_H_
#define FISHC_VERSION_H_

#include <string>

namespace fishc {

const std::string kVersion = "0.1.0";

class VersionPrinter final {
  public:
    VersionPrinter() = delete;
    ~VersionPrinter() = delete;

    static void PrintVersion();
};

}  // namespace fishc

#endif  // FISHC_VERSION_H_
