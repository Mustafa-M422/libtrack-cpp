cmake_minimum_required(VERSION 3.10)

project(libtrack-cpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- wxWidgets Setup (Commit 11) ---
include(FetchContent)
FetchContent_Declare(
    wxWidgets
    GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
    GIT_TAG        v3.2.4
)

# Configure wxWidgets build options BEFORE MakeAvailable
set(wxBUILD_SHARED OFF CACHE BOOL "" FORCE)
set(wxBUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(wxBUILD_TESTS OFF CACHE BOOL "" FORCE)
set(wxBUILD_DEMOS OFF CACHE BOOL "" FORCE)
set(wxBUILD_PRECOMP OFF CACHE BOOL "" FORCE)
set(wxUSE_STL ON CACHE BOOL "" FORCE) # Inteoperability with std items

message(STATUS "Downloading and configuring wxWidgets (this may take a while)...")
FetchContent_MakeAvailable(wxWidgets)

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

# --- GUI Executable (Commit 12) ---
set(GUI_SOURCES
    src/gui/GuiApp.cpp
    src/gui/MainFrame.cpp
)

# WIN32 flag tells CMake to build as a Windows GUI app (not console)
add_executable(libtrack_gui WIN32 ${GUI_SOURCES})

# Link wxWidgets and Core
target_link_libraries(libtrack_gui PRIVATE 
    libtrack_core 
    wx::core 
    wx::base
)

if(MSVC)
    target_compile_options(libtrack_gui PRIVATE /W4)
else()
    target_compile_options(libtrack_gui PRIVATE -Wall -Wextra -Wpedantic)
endif()
