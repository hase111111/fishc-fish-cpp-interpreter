
#include "doctest/doctest.h"

#include "type.h"
#include <variant>

TEST_CASE("Number") {
    using fishc::Number;
    using fishc::ImplInt;
    using fishc::ImplFloat;

    SUBCASE("Operator+") {
        using fishc::operator+;
        SUBCASE("When both are integers, return integer") {
            // Arrange
            const Number a = ImplInt{1};
            const Number b = ImplInt{1};

            // Act
            const Number result = a + b;

            // Assert
            REQUIRE_EQ(std::holds_alternative<ImplInt>(result), true);
            WARN_EQ(std::get<ImplInt>(result), 2);
        }

        SUBCASE("When both are floats, return float") {
            // Arrange
            const Number a = ImplFloat{1.0};
            const Number b = ImplFloat{1.0};

            // Act
            const Number result = a + b;

            // Assert
            REQUIRE_EQ(std::holds_alternative<ImplFloat>(result), true);
            WARN_EQ(std::get<ImplFloat>(result), 2.0);
        }

        SUBCASE("When one is integer and the other is float, return float") {
            // Arrange
            const Number a = ImplInt{1};
            const Number b = ImplFloat{1.0};

            // Act1
            const Number result = a + b;

            // Assert1
            REQUIRE_EQ(std::holds_alternative<ImplFloat>(result), true);
            WARN_EQ(std::get<ImplFloat>(result), 2.0);

            // Act2
            const Number result2 = b + a;

            // Assert2
            REQUIRE_EQ(std::holds_alternative<ImplFloat>(result2), true);
            WARN_EQ(std::get<ImplFloat>(result2), 2.0);
        }
    }

    SUBCASE("Operator-") {
        using fishc::operator-;
        SUBCASE("When both are integers, return integer") {
            // Arrange
            const Number a = ImplInt{1};
            const Number b = ImplInt{1};

            // Act
            const Number result = a - b;

            // Assert
            REQUIRE_EQ(std::holds_alternative<ImplInt>(result), true);
            WARN_EQ(std::get<ImplInt>(result), 0);
        }

        SUBCASE("When both are floats, return float") {
            // Arrange
            const Number a = ImplFloat{1.0};
            const Number b = ImplFloat{1.0};

            // Act
            const Number result = a - b;

            // Assert
            REQUIRE_EQ(std::holds_alternative<ImplFloat>(result), true);
            WARN_EQ(std::get<ImplFloat>(result), 0.0);
        }

        SUBCASE("When one is integer and the other is float, return float") {
            // Arrange
            const Number a = ImplInt{1};
            const Number b = ImplFloat{1.0};

            // Act1
            const Number result = a - b;

            // Assert1
            REQUIRE_EQ(std::holds_alternative<ImplFloat>(result), true);
            WARN_EQ(std::get<ImplFloat>(result), 0.0);

            // Act2
            const Number result2 = b - a;

            // Assert2
            REQUIRE_EQ(std::holds_alternative<ImplFloat>(result2), true);
            WARN_EQ(std::get<ImplFloat>(result2), 0.0);
        }
    }

    SUBCASE("Operator*") {
        using fishc::operator*;
        SUBCASE("When both are integers, return integer") {
            // Arrange
            const Number a = ImplInt{2};
            const Number b = ImplInt{3};

            // Act
            const Number result = a * b;

            // Assert
            REQUIRE_EQ(std::holds_alternative<ImplInt>(result), true);
            WARN_EQ(std::get<ImplInt>(result), 6);
        }

        SUBCASE("When both are floats, return float") {
            // Arrange
            const Number a = ImplFloat{2.0};
            const Number b = ImplFloat{3.0};

            // Act
            const Number result = a * b;

            // Assert
            REQUIRE_EQ(std::holds_alternative<ImplFloat>(result), true);
            WARN_EQ(std::get<ImplFloat>(result), 6.0);
        }

        SUBCASE("When one is integer and the other is float, return float") {
            // Arrange
            const Number a = ImplInt{2};
            const Number b = ImplFloat{3.0};

            // Act1
            const Number result = a * b;

            // Assert1
            REQUIRE_EQ(std::holds_alternative<ImplFloat>(result), true);
            WARN_EQ(std::get<ImplFloat>(result), 6.0);

            // Act2
            const Number result2 = b * a;

            // Assert2
            REQUIRE_EQ(std::holds_alternative<ImplFloat>(result2), true);
            WARN_EQ(std::get<ImplFloat>(result2), 6.0);
        }
    }
}
