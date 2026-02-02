cmake_minimum_required(VERSION 3.10)
project(libtrack-cpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
    include
    include/domain
    include/app
    include/infra
    include/ui
)

# --- main app sources (exclude tests) ---
file(GLOB_RECURSE APP_SOURCES
    "src/*.cpp"
)

add_executable(libtrack-cpp ${APP_SOURCES})

if(MSVC)
    target_compile_options(libtrack-cpp PRIVATE /W4)
else()
    target_compile_options(libtrack-cpp PRIVATE -Wall -Wextra -Wpedantic)
endif()

# --- test executable (optional) ---
add_executable(test_persistence
    tests/test_persistence.cpp
    src/infra/FileRepository.cpp
)

target_compile_options(test_persistence PRIVATE -Wall -Wextra -Wpedantic)
