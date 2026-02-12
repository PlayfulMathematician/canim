set(CANIM_CORE_SRC
    core/core.c
    core/endian.c
    loader/loader.c
    io/pdf.c
    io/utils.c
    math/math_utils.c
    io/image_stb.c
    arena/arena.c
    math/vec2.c 
    math/vec3.c
)

add_library(canim SHARED
    ${CANIM_CORE_SRC}
)
target_compile_definitions(canim 
  PUBLIC 
    CANIM_BUILD 
    $<$<CONFIG:Debug>:CANIM_DEBUG>
    $<$<NOT:$<CONFIG:Debug>>:CANIM_RELEASE>
)
target_include_directories(canim
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
              ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include

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

target_compile_definitions(canim_gl 
  PUBLIC
    CANIM_BUILD 
    $<$<CONFIG:Debug>:CANIM_DEBUG>
    $<$<NOT:$<CONFIG:Debug>>:CANIM_RELEASE>
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
        m
)

if (APPLE)
  target_link_libraries(canim_gl "-framework OpenGL")
elseif(UNIX)
  target_link_libraries(canim_gl PRIVATE EGL::EGL OpenGL::GL)
else()
  message(FATAL_ERROR "Canim is not supported on Windows")
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

