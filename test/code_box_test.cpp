
#include "doctest/doctest.h"

#include "code_box.h"
#include "type.h"


TEST_CASE("CodeBox") {
    using fishc::CodeBox;
    using fishc::Number;
    using fishc::ImplInt;
    using fishc::ImplFloat;
    using fishc::IsInt;
    using fishc::IsFloat;
    using fishc::GetIntOr;

    SUBCASE("GetMaxWidth") {
        SUBCASE("When the code box is empty, Should return 0") {
            // Arrange
            const std::string code = "";
            CodeBox code_box(code);

            // Act
            const auto result = code_box.GetMaxWidth();

            // Assert
            CHECK_EQ(result, 0);
        }

        SUBCASE("When the code is 1 line and 1 characters, Should return 1") {
            // Arrange
            const std::string code = "a";
            CodeBox code_box(code);

            // Act
            const auto result = code_box.GetMaxWidth();

            // Assert
            CHECK_EQ(result, 1);
        }

        SUBCASE("When the code is 1 line and 3 characters, Should return 3") {
            // Arrange
            const std::string code = "abc";
            CodeBox code_box(code);

            // Act
            const auto result = code_box.GetMaxWidth();

            // Assert
            CHECK_EQ(result, 3);
        }

        SUBCASE("When the code is 3 lines, Should return max width") {
            // Arrange
            const std::string code = "a\nab\nabc";
            CodeBox code_box(code);

            // Act
            const auto result = code_box.GetMaxWidth();

            // Assert
            CHECK_EQ(result, 3);
        }
    }

    SUBCASE("GetMaxHeight") {
        SUBCASE("When the code box is empty, Should return 0") {
            // Arrange
            const std::string code = "";
            CodeBox code_box(code);

            // Act
            const auto result = code_box.GetMaxHeight();

            // Assert
            CHECK_EQ(result, 0);
        }

        SUBCASE("When the code is 1 line and 1 characters, Should return 1") {
            // Arrange
            const std::string code = "a";
            CodeBox code_box(code);

            // Act
            const auto result = code_box.GetMaxHeight();

            // Assert
            CHECK_EQ(result, 1);
        }

        SUBCASE("When the code is 1 line, Should return 1") {
            // Arrange
            const std::string code = "abc";
            CodeBox code_box(code);

            // Act
            const auto result = code_box.GetMaxHeight();

            // Assert
            CHECK_EQ(result, 1);
        }

        SUBCASE("When the code is 3 lines, Should return 3") {
            // Arrange
            const std::string code = "a\nab\nabc";
            CodeBox code_box(code);

            // Act
            const auto result = code_box.GetMaxHeight();

            // Assert
            CHECK_EQ(result, 3);
        }
    }

    SUBCASE("GetChar") {
        SUBCASE("When the code is 'a' and get (0, 0), Should return 'a'") {
            // Arrange
            const std::string code = "a";
            CodeBox code_box(code);

            // Act
            const auto result = code_box.GetChar(0, 0);

            // Assert
            CHECK(IsInt(result));
            CHECK_EQ(GetIntOr(result, -1), static_cast<ImplInt>('a'));
        }

        SUBCASE("When the code is 'abc' and get (0, 0), Should return 'a'") {
            // Arrange
            const std::string code = "abc";
            CodeBox code_box(code);

            // Act
            const auto result = code_box.GetChar(0, 0);

            // Assert
            CHECK(IsInt(result));
            CHECK_EQ(GetIntOr(result, -1), static_cast<ImplInt>('a'));
        }

        SUBCASE("When the code is 'abc' and get (1, 0), Should return 'b'") {
            // Arrange
            const std::string code = "abc";
            CodeBox code_box(code);

            // Act
            const auto result = code_box.GetChar(1, 0);

            // Assert
            CHECK(IsInt(result));
            CHECK_EQ(GetIntOr(result, -1), static_cast<ImplInt>('b'));
        }

        // Out of range test
        SUBCASE("When the code is 'abc' and get (3, 0), Should return 0") {
            // Arrange
            const std::string code = "abc";
            CodeBox code_box(code);

            // Act
            const auto result = code_box.GetChar(3, 0);

            // Assert
            CHECK(IsInt(result));
            CHECK_EQ(GetIntOr(result, -1), static_cast<ImplInt>(0));
        }

        SUBCASE("When the code is 'abc' and get (0, 1), Should return 0") {
            // Arrange
            const std::string code = "abc";
            CodeBox code_box(code);

            // Act
            const auto result = code_box.GetChar(0, 1);

            // Assert
            CHECK(IsInt(result));
            CHECK_EQ(GetIntOr(result, -1), static_cast<ImplInt>(0));
        }

        SUBCASE("When the code is 'abc/de/fgh' and get (2, 2), Should return h") {
            // Arrange
            const std::string code = "abc\nde\nfgh";
            CodeBox code_box(code);

            // Act
            const auto result = code_box.GetChar(2, 2);

            // Assert
            CHECK(IsInt(result));
            CHECK_EQ(GetIntOr(result, -1), static_cast<ImplInt>('h'));
        }

        SUBCASE("When the code is 'abc/de/fgh' and get (2, 1), Should return 0") {
            // Arrange
            const std::string code = "abc\nde\nghi";
            CodeBox code_box(code);

            // Act
            const auto result = code_box.GetChar(2, 1);

            // Assert
            CHECK(IsInt(result));
            CHECK_EQ(GetIntOr(result, -1), static_cast<ImplInt>(0));
        }

        SUBCASE("When the code is ' ' and get (0, 0), Should return 32 (SPC)") {
            // Arrange
            const std::string code = " ";
            CodeBox code_box(code);

            // Act
            const auto result = code_box.GetChar(0, 0);

            // Assert
            CHECK(IsInt(result));
            CHECK_EQ(GetIntOr(result, -1), static_cast<ImplInt>(' '));
        }
    }
}
