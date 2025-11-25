cmake_minimum_required(VERSION 3.10)


project(CanimSources LANGUAGES C)


set(CMAKE_C_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
list(FILTER ALL_SRC EXCLUDE REGEX "src/gfx/.*")

add_library(canim SHARED ${ALL_SRC})

target_include_directories(canim PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(canim PRIVATE m)

add_library(canim_gl SHARED gfx/gl.c)

target_include_directories(canim_gl PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

target_link_libraries(canim_gl PRIVATE glad SDL2 EGL GL m)

set_target_properties(canim PROPERTIES
    INSTALL_RPATH "/usr/local/lib/canim"
    BUILD_RPATH "/usr/local/lib/canim"
)

set_target_properties(canim_gl PROPERTIES
    INSTALL_RPATH "/usr/local/lib/canim"
    BUILD_RPATH "/usr/local/lib/canim"
    OUTPUT_NAME "canim_gl"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/canim"
)

install(TARGETS canim
    LIBRARY DESTINATION lib/canim
)

install(TARGETS canim_gl
    LIBRARY DESTINATION lib/canim
)

configure_file("${CMAKE_SOURCE_DIR}/pkgconfig/libcanim.pc.in" 
               "${CMAKE_BINARY_DIR}/libcanim.pc" @ONLY)
configure_file("${CMAKE_SOURCE_DIR}/pkgconfig/libcanim_gl.pc.in" 
               "${CMAKE_BINARY_DIR}/libcanim_gl.pc" @ONLY)

install(FILES "${CMAKE_BINARY_DIR}/libcanim.pc" DESTINATION lib/pkgconfig RENAME "canim.pc")
install(FILES "${CMAKE_BINARY_DIR}/libcanim_gl.pc" DESTINATION lib/pkgconfig RENAME "canim_gl.pc")
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)

set(CMAKE_INSTALL_RPATH "/usr/local/lib/canim")
set(CMAKE_BUILD_RPATH "/usr/local/lib/canim")
