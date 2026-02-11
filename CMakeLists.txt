cmake_minimum_required(VERSION 3.10)
project(Canim VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()
add_subdirectory(src)
add_subdirectory(tests)
install(
    DIRECTORY include/
    DESTINATION include
)

