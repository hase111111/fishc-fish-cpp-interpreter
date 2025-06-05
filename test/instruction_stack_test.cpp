
#include "doctest/doctest.h"

#include "instruction_handler.h"
#include "type.h"

TEST_CASE("InstructionHandler") {
    using fishc::InstructionHandler;
    using fishc::FishResource;
    using fishc::Number;

    SUBCASE("Handle") {
        SUBCASE("When arg is [, Add a new stack") {
            // stack [[1 2 3 2]] -> [[1] [2 3]] 
            
            // Arrange 1
            const char ch = '[';
            const auto fish_resource = std::make_shared<FishResource>("");
            InstructionHandler instruction_handler(fish_resource);
            fish_resource->stack_.default_stack.push_back(1);
            fish_resource->stack_.default_stack.push_back(2);
            fish_resource->stack_.default_stack.push_back(3);
            fish_resource->stack_.default_stack.push_back(2);

            // Act 1
            const auto result = instruction_handler.Handle(ch);

            // Assert 1
            CHECK(result);
            CHECK_EQ(fish_resource->stack_.default_stack.size(), 1);
            CHECK_EQ(fish_resource->stack_.default_stack[0], Number(1));
            CHECK_EQ(fish_resource->stack_.stacks.size(), 1);
            CHECK_EQ(fish_resource->stack_.stacks.back().size(), 2);
            CHECK_EQ(fish_resource->stack_.stacks.back()[0], Number(2));
            CHECK_EQ(fish_resource->stack_.stacks.back()[1], Number(3));
        }

        SUBCASE("When arg is [, Add a new stack with multiple elements") {
            // stack [[10 20 30 40 50 2 4]]
            // -> [[10 20] [30 40 50 2]]  Act 1
            // -> [[10 20] [30] [40 50]]  Act 2

            // Arrange 1
            const char ch = '[';
            const auto fish_resource = std::make_shared<FishResource>("");
            InstructionHandler instruction_handler(fish_resource);
            fish_resource->stack_.default_stack.push_back(10);
            fish_resource->stack_.default_stack.push_back(20);
            fish_resource->stack_.default_stack.push_back(30);
            fish_resource->stack_.default_stack.push_back(40);
            fish_resource->stack_.default_stack.push_back(50);
            fish_resource->stack_.default_stack.push_back(2);
            fish_resource->stack_.default_stack.push_back(4);

            // Act 1
            const auto result1 = instruction_handler.Handle(ch);

            // Assert 1
            CHECK(result1);
            CHECK_EQ(fish_resource->stack_.default_stack.size(), 2);
            CHECK_EQ(fish_resource->stack_.default_stack[0], Number(10));
            CHECK_EQ(fish_resource->stack_.default_stack[1], Number(20));
            CHECK_EQ(fish_resource->stack_.stacks.size(), 1);
            CHECK_EQ(fish_resource->stack_.stacks.back().size(), 4);
            CHECK_EQ(fish_resource->stack_.stacks.back()[0], Number(30));
            CHECK_EQ(fish_resource->stack_.stacks.back()[1], Number(40));
            CHECK_EQ(fish_resource->stack_.stacks.back()[2], Number(50));
            CHECK_EQ(fish_resource->stack_.stacks.back()[3], Number(2));

            // Act 2
            const auto result2 = instruction_handler.Handle(ch);

            // Assert 2
            CHECK(result2);
            CHECK_EQ(fish_resource->stack_.default_stack.size(), 2);
            CHECK_EQ(fish_resource->stack_.default_stack[0], Number(10));
            CHECK_EQ(fish_resource->stack_.default_stack[1], Number(20));
            CHECK_EQ(fish_resource->stack_.stacks.size(), 2);
            CHECK_EQ(fish_resource->stack_.stacks[0].size(), 1);
            CHECK_EQ(fish_resource->stack_.stacks[0][0], Number(30));
            CHECK_EQ(fish_resource->stack_.stacks[1].size(), 2);
            CHECK_EQ(fish_resource->stack_.stacks[1][0], Number(40));
            CHECK_EQ(fish_resource->stack_.stacks[1][1], Number(50));
        }
    }
}
