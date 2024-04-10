cmake_minimum_required(VERSION 3.0)

# Create a new project
project(HelloWorld)

# Add an executable
add_executable(HelloWorld main.c)

# Import the library from the git repo
include(FetchContent)

FetchContent_Declare(
  rsa
  GIT_REPOSITORY https://github.com/adam-mcdaniel/rsa
  GIT_TAG        main
)

FetchContent_MakeAvailable(rsa)

# Include the header only library
include_directories(${rsa_SOURCE_DIR})