
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
    }

    SUBCASE("SetNeedArgument") {
        Argument arg = Argument{{"-h", "--help"}, "Show help message"}
            .SetNeedArgument(true, "<script>", Argument::Type::kString);

        CHECK_EQ(arg.need_argument, true);
        CHECK_EQ(arg.argument_name, "<script>");
        CHECK_EQ(arg.argument_type, Argument::Type::kString);
    }

    SUBCASE("SetIsRequired") {
        Argument arg = Argument{{"-h", "--help"}, "Show help message"}
            .SetIsRequired(true, 0);

        CHECK_EQ(arg.is_required, true);
        CHECK_EQ(arg.required_group, 0);

        arg.SetIsRequired(false, 1);
        CHECK_EQ(arg.is_required, false);
        CHECK_EQ(arg.required_group, 1);
    }

    SUBCASE("SetIsOption") {
        Argument arg = Argument{{"-h", "--help"}, "Show help message"}
            .SetIsOption(true);

        CHECK_EQ(arg.is_option, true);

        arg.SetIsOption(false);
        CHECK_EQ(arg.is_option, false);
    }
}
