
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

# Add Library
add_library(fishc_library STATIC ${SOURCES})

# Include the include directory
target_include_directories(fishc_library PRIVATE ${PROJECT_SOURCE_DIR}/include)
