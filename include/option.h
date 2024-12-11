
#ifndef FISHC_OPTION_H_
#define FISHC_OPTION_H_

#include <string>

namespace fishc {

enum class OptionMode : int {
    kHelp = 0,
    kVersion,
    kCode,
    kStack,
    kValue,
    kTick,
    kAlwaysTick,
    kUnknown
};

struct Option final
{    
    bool is_help_mode{false};
    bool is_version_mode{false};
    std::string code;

};


}  // namespace fishc

#endif  // FISHC_OPTION_H_
