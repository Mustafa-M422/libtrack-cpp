cmake_minimum_required(VERSION 3.10)

project(libtrack-cpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Core Library ---
# Contains Domain, Application, and Infrastructure layers.
# No UI code should be here.
set(CORE_SOURCES
    src/app/LibraryService.cpp
    src/infra/FileRepository.cpp
)

add_library(libtrack_core STATIC ${CORE_SOURCES})

# Export include directories so targets linking to this library can see headers
target_include_directories(libtrack_core PUBLIC 
    include
)

if(MSVC)
    target_compile_options(libtrack_core PRIVATE /W4)
else()
    target_compile_options(libtrack_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

# --- CLI Executable ---
# Contains the Console UI and Entry Point.
set(CLI_SOURCES
    src/main.cpp
    src/ui/ConsoleUI.cpp
)

add_executable(libtrack_cli ${CLI_SOURCES})

# Link to Core
target_link_libraries(libtrack_cli PRIVATE libtrack_core)

if(MSVC)
    target_compile_options(libtrack_cli PRIVATE /W4)
else()
    target_compile_options(libtrack_cli PRIVATE -Wall -Wextra -Wpedantic)
endif()
