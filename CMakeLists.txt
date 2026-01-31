cmake_minimum_required(VERSION 3.10)

project(libtrack-cpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependencies
# (Reserved for FTXUI later)

# Sources
file(GLOB_RECURSE SOURCES 
    "src/domain/*.cpp"
    "src/app/*.cpp"
    "src/infra/*.cpp"
    "src/ui/*.cpp"
    "src/main.cpp"
)

# Executable
add_executable(libtrack-cpp ${SOURCES})

# Include directories (Modern Target-based)
target_include_directories(libtrack-cpp PRIVATE
    include
    include/domain
    include/app
    include/infra
    include/ui
)

# Compiler warnings/options
if(MSVC)
    target_compile_options(libtrack-cpp PRIVATE /W4 /permissive- /Zc:__cplusplus)
else()
    target_compile_options(libtrack-cpp PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif()

