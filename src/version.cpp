
#include <iostream>

#include "version.h"

namespace fishc {

void VersionPrinter::PrintVersion() {
    std::cout << "Version: " << kVersion << std::endl;
}

}  // namespace fishc
