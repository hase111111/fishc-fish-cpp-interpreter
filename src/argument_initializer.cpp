
#include "argument_initializer.h"

#include "argument.h"

namespace fishc {

std::vector<Argument> ArgumentInitializer::Initialize() const noexcept {
    const auto script = 
        Argument{{"script"}, ".fish file path to execute."}
            .IsRequired(1)
            .NeedValue("file path", Argument::Type::kString);

    const auto code_argument = 
        Argument{{"-c", "--code"}, "String of instructions to execute."}
            .IsOption()
            .IsRequired(1)
            .NeedValue("code", Argument::Type::kString);

    const auto help_option = 
        Argument{{"-h", "--help"}, "Show help message, and exit."}
            .IsOption()
            .IsInfoOption();

    const auto tick_argument = 
        Argument{{"-t", "--tick"}, "Define a tick time (second), "
            "or a delay between the execution of each instruction."}
            .IsOption()
            .NeedValue("tick(float)", Argument::Type::kInt);

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
            .NeedValue("default stack", Argument::Type::kString);

    const auto number_argument = 
        Argument{{"-n", "--number"},
            "Define a number to be used as the default stack."}
            .IsOption()
            .NeedValue("default stack", Argument::Type::kInt);

    const auto version_argument = 
        Argument{{"-v", "--version"}, "Show version information, and exit."}
            .IsOption()
            .IsInfoOption();

    const auto play_animation_argument = 
        Argument{{"-p", "--play-animation"}, "Play the animation."}
            .IsOption();

    const auto limit_argument = 
        Argument{{"-l", "--limit"}, "Limit the number of instructions"
            " that can be executed."}
            .IsOption()
            .NeedValue("limit", Argument::Type::kInt);

    return {
            script,
            code_argument,
            help_option, 
            tick_argument,
            always_tick_argument,
            string_argument,
            number_argument,
            version_argument,
            play_animation_argument,
            limit_argument
        };
}

}  // namespace fishc
