
cmake_minimum_required(VERSION 3.10)
project(GLAD LANGUAGES C)

add_library(glad SHARED ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
)

set_target_properties(glad PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    C_STANDARD 17
)

