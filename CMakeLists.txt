cmake_minimum_required(VERSION 3.10)
project(Canim LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Optional flags
option(CANIM_ENABLE_VULKAN "Enable Vulkan backend" ON)
option(CANIM_BUILD_TESTS "Build tests" OFF)

# Add subdirectories
add_subdirectory(external)
add_subdirectory(src)



