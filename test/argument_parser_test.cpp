
#include "doctest/doctest.h"

#include <string>
#include <vector>

#include "argument.h"
#include "argument_parser.h"

// TEST_CASE("ArgumentParser") {
//     using fishc::Argument;
//     using fishc::ArgumentParser;

//     SUBCASE("Parse") {
//         SUBCASE("When there is no argument, Should return true") {
//             // Arrange
//             const auto arg = Argument{{"-h", "--help"}, "message"}.IsOption();
//             ArgumentParser parser({arg});
//             int argc = 1;
//             char* argv[] = {(char*)"program_name"};

//             // Act
//             const auto result = parser.Parse(argc, argv);

//             // Assert
//             CHECK_EQ(result, true);
//         }

//     }
// }
