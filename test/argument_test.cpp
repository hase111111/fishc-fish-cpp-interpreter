
#include "doctest/doctest.h"

#include "argument.h"

TEST_CASE("Argument") {
    using fishc::Argument;

    SUBCASE("Constructor") {
        Argument arg({"-h", "--help"}, "Show help message");
        CHECK_EQ(arg.names.size(), 2);
        CHECK_EQ(arg.names[0], "-h");
        CHECK_EQ(arg.names[1], "--help");
        CHECK_EQ(arg.description, "Show help message");

        CHECK_EQ(arg.need_value, false);
        CHECK_EQ(arg.is_option, false);
        CHECK_EQ(arg.is_required, false);
    }

    SUBCASE("NeedValue") {
        Argument arg = Argument{{"-h", "--help"}, "Show help message"}
            .NeedValue("script", Argument::Type::kString);

        SUBCASE("Should need_value be true") {
            CHECK_EQ(arg.need_value, true);
        }

        SUBCASE("When arg is script, Should value_name be script") {
            CHECK_EQ(arg.value_name, "script");
        }

        SUBCASE("When arg is kString, Should value_type be kString") {
            CHECK_EQ(arg.value_type, Argument::Type::kString);
        }
    }

    SUBCASE("IsRequired") {
        Argument arg = Argument{{"-h", "--help"}, "Show help message"}
            .IsRequired(1);

        SUBCASE("Should is_required be true") {
            CHECK_EQ(arg.is_required, true);
        }

        SUBCASE("When arg is 1, Should required_group be 1") {
            CHECK_EQ(arg.required_group, 1);
        }
    }

    SUBCASE("IsOption") {
        Argument arg = Argument{{"-h", "--help"}, "Show help message"}
            .IsOption();

        SUBCASE("Should is_option be true") {
            CHECK_EQ(arg.is_option, true);
        }
    }
}
