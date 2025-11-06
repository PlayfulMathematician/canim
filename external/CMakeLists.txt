add_library(glad STATIC glad/glad.c)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
)
set_target_properties(glad PROPERTIES
    C_STANDARD 17
    POSITION_INDEPENDENT_CODE ON
)
target_compile_options(glad PRIVATE -Wall -Wextra -Wno-unused-parameter)



