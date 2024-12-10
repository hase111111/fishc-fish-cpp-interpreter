
# Automatically find all .cpp files in the current directory
file(GLOB SOURCES "*.cpp")

# Add the executable
add_executable(fishc ${SOURCES})

# Include the include directory
target_include_directories(fishc PRIVATE ${PROJECT_SOURCE_DIR}/include)
