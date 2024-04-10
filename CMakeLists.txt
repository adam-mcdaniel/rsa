# A CMakeLists.txt file for the header-only library

# Set the minimum required version of CMake for a project
cmake_minimum_required(VERSION 3.0)

# Set the project name
project(rsa)

# Set the C standard to ANSI C
set(CMAKE_C_STANDARD 99)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add the source file `regex.hpp` to the project
add_library(rsa INTERFACE rsa.h)

# Add the CLI test executable to the project
add_executable(cli cli.c)
# add_executable(test1 tests/test1.c)
# add_executable(test2 tests/test2.c)
# add_executable(test3 tests/test3.c)

# Add debug flags
set(CMAKE_C_FLAGS_DEBUG "-g")

# Import the library from the git repo
include(FetchContent)

FetchContent_Declare(
  bigint
  GIT_REPOSITORY https://github.com/adam-mcdaniel/bigint
  GIT_TAG        main
)

FetchContent_MakeAvailable(bigint)

# Include the header only library
include_directories(${bigint_SOURCE_DIR})

# add_executable(test3 tests/test3.c)

# Add the test to the project
enable_testing()

# Add the test to the project
# add_test(NAME test1 COMMAND test1)
# add_test(NAME test2 COMMAND test2)
# add_test(NAME test3 COMMAND test3)