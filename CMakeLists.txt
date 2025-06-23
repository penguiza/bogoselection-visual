cmake_minimum_required(VERSION 3.15)
project(bogo_selection_visual)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use vcpkg toolchain if available (optional fallback)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

# Add executable
add_executable(bogo_selection_visual main.cpp)

# Find SDL2 via vcpkg
find_package(SDL2 REQUIRED)

# Link SDL2
target_link_libraries(bogo_selection_visual PRIVATE SDL2::SDL2 SDL2::SDL2main)

# On Windows, define SDL_MAIN_HANDLED
if(WIN32)
    target_compile_definitions(bogo_selection_visual PRIVATE SDL_MAIN_HANDLED)
endif()
