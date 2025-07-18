cmake_minimum_required(VERSION 3.16)
project(CppDesignPatterns VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Include directories
include_directories(include)
include_directories(src)

# Create library for pattern implementations
file(GLOB_RECURSE PATTERN_SOURCES
    "src/creational/*.cpp"
    "src/structural/*.cpp"
    "src/behavioral/*.cpp"
)

file(GLOB_RECURSE PATTERN_HEADERS
    "include/*.h"
    "src/creational/*.h"
    "src/structural/*.h"
    "src/behavioral/*.h"
)

# Create static library
add_library(DesignPatterns STATIC ${PATTERN_SOURCES} ${PATTERN_HEADERS})

# Demo executables
file(GLOB DEMO_SOURCES "demos/*.cpp")

foreach(demo_source ${DEMO_SOURCES})
    get_filename_component(demo_name ${demo_source} NAME_WE)
    add_executable(${demo_name} ${demo_source})
    target_link_libraries(${demo_name} DesignPatterns)
endforeach()

# Main demo runner
add_executable(all_patterns_demo demos/all_patterns_demo.cpp)
target_link_libraries(all_patterns_demo DesignPatterns)

# Install targets
install(TARGETS DesignPatterns
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(FILES ${PATTERN_HEADERS} DESTINATION include)

# Enable testing
enable_testing()

# Add custom target for running all demos
add_custom_target(run_all_demos
    COMMAND echo "Running all C++ Design Pattern Demos..."
    COMMAND echo "======================================="
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(DesignPatterns PRIVATE -fPIC)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(DesignPatterns PRIVATE -fPIC)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(DesignPatterns PRIVATE /W4)
endif()

# Print build configuration
message(STATUS "C++ Design Patterns Project Configuration:")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Install Prefix: ${CMAKE_INSTALL_PREFIX}")
