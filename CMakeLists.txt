cmake_minimum_required(VERSION 3.15)
project(bogosort_visual)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use vcpkg toolchain if available (optional fallback)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

# Add your source file(s) here — replace with actual filenames if needed
add_executable(bogosort_visual main.cpp)

# Find SDL2 and SDL2_mixer via vcpkg
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Link SDL2 and SDL2_mixer
target_link_libraries(bogosort_visual PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2_mixer::SDL2_mixer)

# On Windows, define SDL_MAIN_HANDLED
if(WIN32)
    target_compile_definitions(bogosort_visual PRIVATE SDL_MAIN_HANDLED)
endif()
