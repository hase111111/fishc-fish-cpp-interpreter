
cmake_minimum_required(VERSION 3.10) # Set the minimum required version of CMake

# Set the project name and version
project(FishC VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the subdirectory containing the source code
add_subdirectory(src)

# Optionally include the include directory for other purposes
include_directories(${PROJECT_SOURCE_DIR}/include)
