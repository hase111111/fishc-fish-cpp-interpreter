
#include "option.h"

#include <cassert>

namespace fishc {

OptionMode ArgToOptionMode(const std::string& arg) {
    assert(arg.size() > 0);
    assert(IsOption(arg));

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
    } else if (arg == "-f" || arg == "--file") {
        return OptionMode::kFile;
    } else {
        return OptionMode::kUnknown;
    }
}

bool IsOption(const std::string& arg) {
    if (arg.size() == 0) {
        return false;
    }

    return arg[0] == '-';
}

}  // namespace fishc
