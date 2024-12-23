
#include "doctest/doctest.h"

#include "instruction_handler.h"

TEST_CASE("InstructionHandler") {
    using fishc::InstructionHandler;
    using Dir = fishc::FishResource::Direction;

    const auto fish_resource = std::make_shared<fishc::FishResource>("");
    const auto default_resource = std::make_shared<const fishc::FishResource>("");
    InstructionHandler instruction_handler(fish_resource);

    // Movement and execution
    SUBCASE("Handle") {
        SUBCASE("When arg is >, Change the direction to right") {
            // Arrange
            const char ch = '>';

            // Act
            const auto result = instruction_handler.Handle(ch);

            // Assert
            CHECK_EQ(fish_resource->direction_, Dir::kRight);
            CHECK(result);
        }

        SUBCASE("When arg is <, Change the direction to left") {
            // Arrange
            const char ch = '<';

            // Act
            const auto result = instruction_handler.Handle(ch);

            // Assert
            CHECK_EQ(fish_resource->direction_, Dir::kLeft);
            CHECK(result);
        }

        SUBCASE("When arg is ^, Change the direction to up") {
            // Arrange
            const char ch = '^';

            // Act
            const auto result = instruction_handler.Handle(ch);

            // Assert
            CHECK_EQ(fish_resource->direction_, Dir::kUp);
            CHECK(result);
        }

        SUBCASE("When arg is v, Change the direction to down") {
            // Arrange
            const char ch = 'v';

            // Act
            const auto result = instruction_handler.Handle(ch);

            // Assert
            CHECK_EQ(fish_resource->direction_, Dir::kDown);
            CHECK(result);
        }

        CHECK_EQ(fish_resource->code_box_, default_resource->code_box_);
        CHECK_EQ(fish_resource->register_, default_resource->register_);
        CHECK_EQ(fish_resource->stack_, default_resource->stack_);
        CHECK_EQ(fish_resource->x_, default_resource->x_);
        CHECK_EQ(fish_resource->y_, default_resource->y_);
        CHECK_EQ(fish_resource->skip_, default_resource->skip_);
        CHECK_EQ(fish_resource->use_double_quote_, default_resource->use_double_quote_);
        CHECK_EQ(fish_resource->use_single_quote_, default_resource->use_single_quote_);
    }
}
