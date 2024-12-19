
#include "doctest/doctest.h"

#include <string>
#include <vector>

#include "argument.h"
#include "argument_validator.h"


TEST_CASE("ArgumentValidator") {
    using fishc::Argument;
    using fishc::ArgumentValidator;
    using Input = const std::vector<std::string>;

    SUBCASE("Validate") {
        SUBCASE("When there is no argument, Should return true") {
            // Arrange
            const auto arg = Argument{{"-h", "--help"}, "message"}.IsOption();
            ArgumentValidator validator({arg});
            Input empty = {"program_name"};

            // Act
            const auto result = validator.Validate(empty);

            // Assert
            CHECK_EQ(result, true);
        }

        SUBCASE("When known option is provided, Should return true") {
            // Arrange1
            const auto arg = Argument{{"-h", "--help"}, "message"}.IsOption();
            ArgumentValidator validator({arg});
            Input argv1 = {"program_name", "-h"};

            // Act1
            const auto result1 = validator.Validate(argv1);

            // Assert1
            CHECK_EQ(result1, true);

            // Arrange2
            Input argv2 = {"program_name", "--help"};

            // Act2
            const auto result2 = validator.Validate(argv2);

            // Assert2
            CHECK_EQ(result2, true);
        }

        SUBCASE("When unknown option is provided, Should return false") {
            // Arrange
            const auto arg = Argument{{"-h", "--help"}, "message"}.IsOption();
            ArgumentValidator validator({arg});
            Input argv = {"program_name", "-u"};

            // Act
            const auto result = validator.Validate(argv);

            // Assert
            CHECK_EQ(result, false);
        }

        SUBCASE("When multiple option is provided, Should return false") {
            // Arrange1
            const auto arg = Argument{{"-h", "--help"}, "message"}.IsOption();
            ArgumentValidator validator({arg});
            Input argv1 = {"program_name", "-h", "-h"};

            // Act1
            const auto result1 = validator.Validate(argv1);

            // Assert1
            CHECK_EQ(result1, false);

            // Arrange2
            Input argv2 = {"program_name", "--h", "--help"};

            // Act2
            const auto result2 = validator.Validate(argv2);

            // Assert2
            CHECK_EQ(result2, false);
        }

        SUBCASE("When option needs value but not provided, Should return false") {
            // Arrange1
            const auto arg1 = Argument{{"-h"}, "message"}
                .IsOption()
                .NeedValue("arg", Argument::Type::kString);
            const auto arg2 = Argument{{"-v"}, "message"}
                .IsOption();
            ArgumentValidator validator({arg1, arg2});
            Input argv1 = {"program_name", "-h"};

            // Act1
            const auto result1 = validator.Validate(argv1);

            // Assert1
            CHECK_EQ(result1, false);

            // Arrange2
            Input argv2 = {"program_name", "-h", "-v"};

            // Act2
            const auto result2 = validator.Validate(argv2);

            // Assert2
            CHECK_EQ(result2, false);
        }

        SUBCASE("When option needs value and provided, Should return true") {
            // Arrange
            const auto arg = Argument{{"-h"}, "message"}
                .IsOption()
                .NeedValue("arg", Argument::Type::kString);
            ArgumentValidator validator({arg});
            Input argv = {"program_name", "-h", "arg"};

            // Act
            const auto result = validator.Validate(argv);

            // Assert
            CHECK_EQ(result, true);
        }

        SUBCASE("When required argument is not provided, Should return false") {
            // Arrange
            const auto arg = Argument{{"-h"}, "message"}
                .IsOption()
                .IsRequired(1);
            ArgumentValidator validator({arg});
            Input argv = {"program_name"};

            // Act
            const auto result = validator.Validate(argv);

            // Assert
            CHECK_EQ(result, false);
        }

        SUBCASE("When required argument is provided, Should return true") {
            // Arrange
            const auto arg = Argument{{"-h"}, "message"}
                .IsOption()
                .IsRequired(1);
            ArgumentValidator validator({arg});
            Input argv = {"program_name", "-h"};

            // Act
            const auto result = validator.Validate(argv);

            // Assert
            CHECK_EQ(result, true);
        }

        SUBCASE("When required argument is not provided "
            "but provided info option, Should return true") {
            // Arrange
            const auto arg1 = Argument{{"-h"}, "message"}
                .IsOption()
                .IsRequired(1);
            const auto arg2 = Argument{{"-s"}, "message"}
                .IsOption()
                .IsInfoOption();
            ArgumentValidator validator({arg1, arg2});
            Input argv = {"program_name", "-s"};

            // Act
            const auto result = validator.Validate(argv);

            // Assert
            CHECK_EQ(result, true);
        }

        SUBCASE("When required argument is provided but not enough, Should return false") {
            // Arrange
            const auto arg1 = Argument{{"-h"}, "message"}
                .IsOption()
                .IsRequired(1);
            const auto arg2 = Argument{{"-i"}, "message"}
                .IsOption()
                .IsRequired(2);
            ArgumentValidator validator({arg1, arg2});
            Input argv = {"program_name", "-h"};

            // Act
            const auto result = validator.Validate(argv);

            // Assert
            CHECK_EQ(result, false);
        }

        SUBCASE("When required argument is provided enough, Should return true") {
            // Arrange
            const auto arg1 = Argument{{"-h"}, "message"}
                .IsOption()
                .IsRequired(1);
            const auto arg2 = Argument{{"-i"}, "message"}
                .IsOption()
                .IsRequired(2);
            ArgumentValidator validator({arg1, arg2});
            Input argv = {"program_name", "-h", "-i"};

            // Act
            const auto result = validator.Validate(argv);

            // Assert
            CHECK_EQ(result, true);
        }

        SUBCASE("When argument need vector type value "
           "and provided three value, Should return true") {
            // Arrange
            const auto arg1 = Argument{{"-h"}, "message"}
                .IsOption()
                .NeedValue("arg", Argument::Type::kVectorInt);
            const auto arg2 = Argument{{"sample"}, "message"}
                .NeedValue("arg", Argument::Type::kInt);
            const auto arg3 = Argument{{"-t"}, "message"}
                .IsOption();
            ArgumentValidator validator({arg1, arg2, arg3});
            Input argv = {"program_name", "-h", "1", "2", "3"};

            // Act
            const auto result = validator.Validate(argv);

            // Assert
            CHECK_EQ(result, true);

            SUBCASE("Case when provided sample -h 1 2 3") {
                // Arrange
                Input argv = {"program_name", "sample", "-h", "1", "2", "3"};

                // Act
                const auto result = validator.Validate(argv);

                // Assert
                CHECK_EQ(result, true);
            }

            SUBCASE("Case when provided -h 1 2 3 -t") {
                // Arrange
                Input argv = {"program_name", "-h", "1", "2", "3", "-t"};

                // Act
                const auto result = validator.Validate(argv);

                // Assert
                CHECK_EQ(result, true);
            }
        }

        SUBCASE("When argument need not vector type value "
           "and provided three value, Should return false") {
            // Arrange
            const auto arg = Argument{{"-h"}, "message"}
                .IsOption()
                .NeedValue("arg", Argument::Type::kString);
            ArgumentValidator validator({arg});
            Input argv = {"program_name", "-h", "1", "2", "3"};

            // Act
            const auto result = validator.Validate(argv);

            // Assert
            CHECK_EQ(result, false);
        }
    }
}
