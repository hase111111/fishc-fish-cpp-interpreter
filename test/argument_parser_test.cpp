
#include "doctest/doctest.h"

#include <string>
#include <vector>

#include "argument.h"
#include "argument_parser.h"

TEST_CASE("ArgumentParser") {
    using fishc::Argument;
    using fishc::ArgumentParser;

    // It may be redundant because it overlaps with ArgumentValidator.
    SUBCASE("Parse") {
        SUBCASE("When there is no argument, Should return true") {
            // Arrange
            const auto arg = Argument{{"-h", "--help"}, "message"}.IsOption();
            ArgumentParser parser({arg});
            int argc = 1;
            char* argv[] = {(char*)"program_name"};

            // Act
            const auto result = parser.Parse(argc, argv);

            // Assert
            CHECK_EQ(result, true);
        }

        SUBCASE("When there is an invalid argument, Should return false") {
            // Arrange
            const auto arg = Argument{{"-h", "--help"}, "message"}.IsOption();
            ArgumentParser parser({arg});
            int argc = 2;
            char* argv[] = {(char*)"program_name", (char*)"--invalid"};

            // Act
            const auto result = parser.Parse(argc, argv);

            // Assert
            CHECK_EQ(result, false);
        }

        SUBCASE("When there is no required argument, Should return false") {
            // Arrange
            const auto arg = Argument{{"-h", "--help"}, "message"}
                .IsOption()
                .IsRequired(1);
            ArgumentParser parser({arg});
            int argc = 1;
            char* argv[] = {(char*)"program_name"};

            // Act
            const auto result = parser.Parse(argc, argv);

            // Assert
            CHECK_EQ(result, false);
        }

        SUBCASE("When there is a required argument, Should return true") {
            // Arrange
            const auto arg = Argument{{"-h", "--help"}, "message"}
                .IsOption()
                .IsRequired(1);
            ArgumentParser parser({arg});
            int argc = 2;
            char* argv[] = {(char*)"program_name", (char*)"--help"};

            // Act
            const auto result = parser.Parse(argc, argv);

            // Assert
            CHECK_EQ(result, true);
        }

        SUBCASE("When there is a argument which need a value "
            "but there is no value, Should return false") {
            // Arrange
            const auto arg = Argument{{"-h", "--help"}, "message"}
                .IsOption()
                .NeedValue("sample", Argument::Type::kString);

            ArgumentParser parser({arg});
            int argc = 2;
            char* argv[] = {(char*)"program_name", (char*)"--help"};

            // Act
            const auto result = parser.Parse(argc, argv);

            // Assert
            CHECK_EQ(result, false);
        }

        SUBCASE("When there is a argument which need a value "
            "and there is a value, Should return true") {
            // Arrange
            const auto arg = Argument{{"-h", "--help"}, "message"}
                .IsOption()
                .NeedValue("sample", Argument::Type::kString);

            ArgumentParser parser({arg});
            int argc = 3;
            char* argv[] = {(char*)"program_name", (char*)"--help", (char*)"sample"};

            // Act
            const auto result = parser.Parse(argc, argv);

            // Assert
            CHECK_EQ(result, true);
        }
    }

    SUBCASE("HasOption") {
        SUBCASE("When there is no argument, Should return false") {
            // Arrange1
            const auto arg = Argument{{"-h"}, "message"}.IsOption();
            ArgumentParser parser({arg});
            int argc = 1;
            char* argv[] = {(char*)"program_name"};
            parser.Parse(argc, argv);

            // Act1
            const auto result = parser.HasOption("-h");

            // Assert1
            CHECK_EQ(result, false);
        }

        SUBCASE("When there is an argument, Should return true") {
            // Arrange
            const auto arg = Argument{{"-h"}, "message"}.IsOption();
            ArgumentParser parser({arg});
            int argc = 2;
            char* argv[] = {(char*)"program_name", (char*)"-h"};
            parser.Parse(argc, argv);

            // Act
            const auto result = parser.HasOption("-h");

            // Assert
            CHECK_EQ(result, true);
        }

        SUBCASE("When option is not found, Should return false") {
            // Arrange
            const auto arg = Argument{{"-h"}, "message"}.IsOption();
            ArgumentParser parser({arg});
            int argc = 2;
            char* argv[] = {(char*)"program_name", (char*)"-h"};
            parser.Parse(argc, argv);

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
            int argc = 2;
            char* argv[] = {(char*)"program_name", (char*)"-h"};
            parser.Parse(argc, argv);

            // Act
            const auto result = parser.HasOption("--help");

            // Assert
            CHECK_EQ(result, true);
        }
    }
}
