
# Automatically find all .cpp files in the current directory
file(GLOB SOURCES "*.cpp")

# Add Library
add_library(fishc_library STATIC ${SOURCES})

# Include the include directory
target_include_directories(fishc_library PRIVATE ${PROJECT_SOURCE_DIR}/include)
