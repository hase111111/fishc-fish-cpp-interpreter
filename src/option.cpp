
#include "option.h"

namespace fishc {

OptionMode ArgToOptionMode(const std::string& arg) {
    if (arg == "-h" || arg == "--help") {
        return OptionMode::kHelp;
    } else if (arg == "-v" || arg == "--version") {
        return OptionMode::kVersion;
    } else if (arg == "-c" || arg == "--code") {
        return OptionMode::kCode;
    } else if (arg == "-s" || arg == "--stack") {
        return OptionMode::kStack;
    } else if (arg == "-V" || arg == "--value") {
        return OptionMode::kValue;
    } else if (arg == "-t" || arg == "--tick") {
        return OptionMode::kTick;
    } else if (arg == "-a" || arg == "--always-tick") {
        return OptionMode::kAlwaysTick;
    } else {
        return OptionMode::kUnknown;
    }
}

}  // namespace fishc
