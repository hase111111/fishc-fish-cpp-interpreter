
cmake_minimum_required(VERSION 3.11) # Set the minimum required version of CMake
enable_testing() # Enable testing in the project

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the project name and version
project(FishC 
    VERSION 0.1
    DESCRIPTION "This is esolang ><> interpreter."
    LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the subdirectory containing the source code
add_subdirectory(src)
add_subdirectory(test)

# Optionally include the include directory for other purposes
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(fishc main.cpp)

# Link the library to the executable
target_link_libraries(fishc fishc_library)
