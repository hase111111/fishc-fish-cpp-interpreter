
#include <iostream>

#include "version.h"

namespace fishc {

void VersionPrinter::Print() const noexcept {
    std::cout << kProgramName << " version: " << kVersion << std::endl;
}

}  // namespace fishc
