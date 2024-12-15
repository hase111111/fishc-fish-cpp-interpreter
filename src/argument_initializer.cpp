
#include "argument_initializer.h"

#include "argument.h"

namespace fishc {

std::vector<Argument> ArgumentInitializer::Initialize() const noexcept {
    const auto script = 
        Argument{{"script"}, ".fish file path to execute."}
            .IsRequired(1)
            .NeedArgument("file path", Argument::Type::kString);

    const auto code_argument = 
        Argument{{"-c", "--code"}, "String of instructions to execute."}
            .IsOption()
            .IsRequired(1)
            .NeedArgument("code", Argument::Type::kString);

    const auto tick_argument = 
        Argument{{"-t", "--tick"}, "Define a tick time (second), "
            "or a delay between the execution of each instruction."}
            .IsOption()
            .NeedArgument("tick(float)", Argument::Type::kInt);

    const auto always_tick_argument = 
        Argument{{"-a", "--always-tick"}, 
            "Make every instruction cause a tick (delay), "
            "even whitespace and skipped instructions."
            "or a delay between the execution of each instruction."}
            .IsOption();

    const auto string_argument = 
        Argument{{"-s", "--string"},
            "Define a string to be used as the default stack."}
            .IsOption()
            .NeedArgument("default stack", Argument::Type::kString);

    const auto number_argument = 
        Argument{{"-n", "--number"},
            "Define a number to be used as the default stack."}
            .IsOption()
            .NeedArgument("default stack", Argument::Type::kInt);

    const auto version_argument = 
        Argument{{"-v", "--version"}, "Show version information."}
            .IsOption();

    const auto play_animation_argument = 
        Argument{{"-p", "--play-animation"}, "Play the animation."}
            .IsOption();

    return {
            script,
            code_argument, 
            tick_argument,
            always_tick_argument,
            string_argument,
            number_argument,
            version_argument,
            play_animation_argument
        };
}

}  // namespace fishc
