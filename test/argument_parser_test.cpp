
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
}
