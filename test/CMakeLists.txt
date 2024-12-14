
# Automatically find all .cpp files in the current directory
file(GLOB SOURCES "*.cpp")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Warning Level to Maximum
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Include FetchContent module
include(FetchContent)

# Add doctest library
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11 # 利用したいバージョンを指定
)

# Make doctest available to the project
FetchContent_MakeAvailable(doctest)

add_executable(fishc_test ${SOURCES})

# Link the library to the executable
target_link_libraries(fishc_test fishc_library doctest::doctest)

# Enable testing in the project
add_test(
  NAME fishc_test # test name
  COMMAND fishc_test # command to run the test
)
