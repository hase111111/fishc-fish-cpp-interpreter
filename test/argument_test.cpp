
#include "doctest/doctest.h"

#include "argument_parser.h"

TEST_CASE("Argument") {
    using fishc::Argument;

    SUBCASE("Constructor") {
        Argument arg({"-h", "--help"}, "Show help message");
        CHECK_EQ(arg.names.size(), 2);
        CHECK_EQ(arg.names[0], "-h");
        CHECK_EQ(arg.names[1], "--help");
        CHECK_EQ(arg.description, "Show help message");
    }
}