
#include "doctest/doctest.h"

#include <string>
#include <vector>

#include "argument.h"
#include "argument_validator.h"


TEST_CASE("ArgumentValidator") {
    using fishc::Argument;
    using fishc::ArgumentValidator;
    using ArgStrs = const std::vector<std::string>;

    SUBCASE("Constructor") {
        const auto arg1 = Argument{{"-t", "--time"}, "It's show time!"}
            .SetIsOption(true);

        ArgumentValidator validator({arg1});

        SUBCASE("GetErrorReasonString") {
            CHECK_EQ(validator.GetErrorReasonString(), "");
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
            ArgStrs argv1 = {"test", "-t", "-v", "-a", "argument"};
            auto result = validator.Validate(argv1);
            CHECK_EQ(result, true);
        }

        SUBCASE("True case 2") {
            ArgStrs argv2 = {"test", "--time", "--version", "--argument", "argument"};
            auto result = validator.Validate(argv2);
            CHECK_EQ(result, true);
        }

        SUBCASE("True case 3") {
            ArgStrs argv3 = {"test", "-t", "--argument", "argument", "--version",};
            auto result = validator.Validate(argv3);
            CHECK_EQ(result, true);
        }

        SUBCASE("False case : Option needs argument") {
            ArgStrs argv = {"test", "-a"};
            CHECK_EQ(validator.Validate(argv), false);

            ArgStrs argv2 = {"test", "-a", "-h"};
            CHECK_EQ(validator.Validate(argv2), false);
        }

        SUBCASE("False case : Unknown argument") {
            ArgStrs argv = {"test", "-q"};
            CHECK_EQ(validator.Validate(argv), false);
        }

        SUBCASE("False case : Multiple option") {
            ArgStrs argv = {"test", "-v", "-v"};
            CHECK_EQ(validator.Validate(argv), false);
        }
    }

    SUBCASE("GetErrorReason") {
        const auto arg1 = Argument{{"-t", "--time"}, "It's show time!"}
            .SetIsOption(true);

        ArgumentValidator validator({arg1});

        // Act
        ArgStrs argv = {"test", "-q"};
        validator.Validate(argv);

        // Assert
        CHECK_EQ(validator.GetErrorReason(), ArgumentValidator::ErrorReason::kUnknownOption);
    }
}