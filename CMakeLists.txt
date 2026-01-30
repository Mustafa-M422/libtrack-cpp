cmake_minimum_required(VERSION 3.10)

project(libtrack-cpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(
    include
    include/domain
    include/app
    include/infra
    include/ui
)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Executable
add_executable(libtrack-cpp ${SOURCES})

# Compile options (Warnings)
if(MSVC)
    target_compile_options(libtrack-cpp PRIVATE /W4)
else()
    target_compile_options(libtrack-cpp PRIVATE -Wall -Wextra -Wpedantic)
endif()
