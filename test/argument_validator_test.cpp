
#include "argument.h"
#include "doctest/doctest.h"

#include "argument_validator.h"

TEST_CASE("ArgumentValidator") {
    using fishc::Argument;
    using fishc::ArgumentValidator;

    SUBCASE("Constructor") {
        const auto arg1 = Argument{{"-t", "--time"}, "It's show time!"}
            .SetIsOption(true);

        ArgumentValidator validator({arg1});

        SUBCASE("GetErrorReasonString") {
            CHECK_EQ(validator.GetErrorReasonString(), "");
        }

        SUBCASE("Add help option") {
            const char *argv[] = {"test", "-h"};
            CHECK_EQ(validator.Validate(2, argv), true);
        }
    }

    SUBCASE("Validate") {
        const auto arg1 = Argument{{"-t", "--time"}, "Show time"}
            .SetIsOption(true);
        const auto arg2 = Argument{{"-v", "--version"}, "Show version"}
            .SetIsOption(true);
        const auto arg3 = Argument{{"-a", "--argument"}, "Need argument"}
            .SetIsOption(true)
            .SetNeedArgument(true, "<argument>", Argument::Type::kString);

        const std::vector<Argument> argument_settings = {arg1, arg2, arg3};
        ArgumentValidator validator(argument_settings);

        SUBCASE("True case 1") {
            const char *argv1[] = {"test", "-t", "-v", "-a", "argument"};
            auto result = validator.Validate(5, argv1);
            CHECK_EQ(result, true);
        }

        SUBCASE("True case 2") {
            const char *argv2[] = {"test", "--time", "--version", "--argument", "argument"};
            auto result = validator.Validate(5, argv2);
            CHECK_EQ(result, true);
        }

        SUBCASE("True case 3") {
            const char *argv3[] = {"test", "-t", "--argument", "argument", "--version",};
            auto result = validator.Validate(5, argv3);
            CHECK_EQ(result, true);
        }

        SUBCASE("False case : Option needs argument") {
            const char *argv[] = {"test", "-a"};
            CHECK_EQ(validator.Validate(2, argv), false);

            const char *argv2[] = {"test", "-a", "-h"};
            CHECK_EQ(validator.Validate(3, argv2), false);
        }

        SUBCASE("False case : Unknown argument") {
            const char *argv[] = {"test", "-q"};
            CHECK_EQ(validator.Validate(2, argv), false);
        }

        SUBCASE("False case : Multiple option") {
            const char *argv[] = {"test", "-v", "-v"};
            CHECK_EQ(validator.Validate(3, argv), false);
        }
    }
}