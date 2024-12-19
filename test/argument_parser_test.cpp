
#include "doctest/doctest.h"

#include <string>
#include <vector>

#include "argument.h"
#include "argument_parser.h"

TEST_CASE("ArgumentParser") {
    using fishc::Argument;
    using fishc::ArgumentParser;
    using Input = std::vector<std::string>;

    SUBCASE("HasOption") {
        SUBCASE("When there is no argument, Should return false") {
            // Arrange1
            const auto arg = Argument{{"-h"}, "message"}.IsOption();
            ArgumentParser parser({arg});
            Input args = {"program_name"};
            parser.Parse(args);

            // Act1
            const auto result = parser.HasOption("-h");

            // Assert1
            CHECK_EQ(result, false);
        }

        SUBCASE("When there is an argument, Should return true") {
            // Arrange
            const auto arg = Argument{{"-h"}, "message"}.IsOption();
            ArgumentParser parser({arg});
            Input args = {"program_name", "-h"};
            parser.Parse(args);

            // Act
            const auto result = parser.HasOption("-h");

            // Assert
            CHECK_EQ(result, true);
        }

        SUBCASE("When option is not found, Should return false") {
            // Arrange
            const auto arg = Argument{{"-h"}, "message"}.IsOption();
            ArgumentParser parser({arg});
            Input args = {"program_name", "-h"};
            parser.Parse(args);

            // Act
            const auto result = parser.HasOption("--help");

            // Assert
            CHECK_EQ(result, false);
        }

        SUBCASE("When argument has multiple names "
            "and one of them is found, Should return true") {
            // Arrange
            const auto arg = Argument{{"-h", "--help"}, "message"}
                .IsOption();
            ArgumentParser parser({arg});
            Input args = {"program_name", "-h"};
            parser.Parse(args);

            // Act
            const auto result = parser.HasOption("--help");

            // Assert
            CHECK_EQ(result, true);
        }
    }

    SUBCASE("GetOptionValue") {
        SUBCASE("When there is no argument, Should return default value") {
            // Arrange
            const auto arg = Argument{{"-h"}, "message"}.IsOption();
            ArgumentParser parser({arg});
            Input args = {"program_name"};
            parser.Parse(args);

            // Act
            const auto result = parser.GetOptionValue<int>("-h");

            // Assert
            CHECK_EQ(result, 0);
        }

        SUBCASE("When there is int type argument and provide 100, "
            "Should return 100") {
            // Arrange
            const auto arg = Argument{{"-h"}, "message"}
                .IsOption()
                .NeedValue("arg", Argument::Type::kInt);
            ArgumentParser parser({arg});
            Input args = {"program_name", "-h", "100"};
            parser.Parse(args);

            // Act
            const auto result = parser.GetOptionValue<int>("-h");

            // Assert
            CHECK_EQ(result, 100);
        }

        SUBCASE("When there is float type argument and provide 1.23f, "
            "Should return 1.23f") {
            // Arrange
            const auto arg = Argument{{"-h"}, "message"}
                .IsOption()
                .NeedValue("arg", Argument::Type::kFloat);
            ArgumentParser parser({arg});
            Input args = {"program_name", "-h", "1.23f"};
            parser.Parse(args);

            // Act
            const auto result = parser.GetOptionValue<float>("-h");

            // Assert
            CHECK_EQ(result, 1.23f);
        }

        SUBCASE("When there is string type argument and provide 'sample', "
            "Should return 'sample'") {
            // Arrange
            const auto arg = Argument{{"-h"}, "message"}
                .IsOption()
                .NeedValue("arg", Argument::Type::kString);
            ArgumentParser parser({arg});
            Input args = {"program_name", "-h", "sample"};
            parser.Parse(args);

            // Act
            const auto result = parser.GetOptionValue<std::string>("-h");

            // Assert
            CHECK_EQ(result, "sample");
        }

        SUBCASE("When there is vector int type argument and provide 1 2 3, "
            "Should return {1, 2, 3}") {
            // Arrange
            const auto arg = Argument{{"-h"}, "message"}
                .IsOption()
                .NeedValue("arg", Argument::Type::kVectorInt);
            ArgumentParser parser({arg});
            Input args = {"program_name", "-h", "1", "2", "3"};
            parser.Parse(args);

            // Act
            const auto result = parser.GetOptionValueVector<int>("-h");

            // Assert
            CHECK_EQ(result, std::vector<int>{1, 2, 3});
        }
    }
}
