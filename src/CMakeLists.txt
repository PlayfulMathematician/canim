cmake_minimum_required(VERSION 3.10)
project(CanimSources LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Collect every .c file under src/ automatically
file(GLOB_RECURSE CANIM_SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

# Build the main shared library
add_library(canim SHARED ${CANIM_SRC})

# Include the public headers
target_include_directories(canim
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Link standard math library if needed
target_link_libraries(canim PRIVATE m)

# Optional install rules
install(TARGETS canim
    LIBRARY DESTINATION lib/canim
)

# ✅ FIXED: Correct header path
install(DIRECTORY ${PROJECT_SOURCE_DIR}/../include/canim
    DESTINATION include
)

