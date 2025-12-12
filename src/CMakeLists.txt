set(CANIM_CORE_SRC
    core/core.c
    core/endian.c
    core/svec.c
    loader/loader.c
)

add_library(canim SHARED
    ${CANIM_CORE_SRC}
)

target_include_directories(canim
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(canim
    PRIVATE
        m
)

set_target_properties(canim PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/canim"
    BUILD_RPATH "${CMAKE_BINARY_DIR}/canim"
    INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/canim"
)

add_library(canim_gl SHARED
    gfx/gl.c
)

target_link_libraries(canim_gl
    PUBLIC
        canim
)

find_package(SDL2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(EGL QUIET)

target_link_libraries(canim_gl
    PRIVATE
        SDL2::SDL2
        glad::glad
        OpenGL::GL
        m
)

if (EGL_FOUND)
  target_link_libraries(canim_gl PRIVATE EGL::EGL)
  target_compile_definitions(canim_gl PRIVATE CANIM_HAVE_EGL=1)
endif()

set_target_properties(canim_gl PROPERTIES
    OUTPUT_NAME "canim_gl"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/canim"
    BUILD_RPATH "${CMAKE_BINARY_DIR}/canim"
    INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/canim"
)

install(TARGETS canim canim_gl
    LIBRARY DESTINATION lib/canim
)

