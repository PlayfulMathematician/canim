set(CANIM_CORE_SRC
    core/endian.c
    loader/loader.c
    io/pdf.c
    io/utils.c
    math/math_utils.c
    io/image_stb.c
    arena/arena.c
    math/vec2.c
    math/vec3.c
    log/log.c
)

add_library(canim SHARED ${CANIM_CORE_SRC})

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
        SYSTEM "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include"
)

target_link_libraries(canim PRIVATE m)

add_library(canim_gl SHARED gfx/gl.c)

target_compile_definitions(canim_gl
    PUBLIC
        CANIM_BUILD
        $<$<CONFIG:Debug>:CANIM_DEBUG>
        $<$<NOT:$<CONFIG:Debug>>:CANIM_RELEASE>
)

target_include_directories(canim_gl PRIVATE SYSTEM "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include")

target_link_libraries(canim_gl
    PUBLIC canim
    PRIVATE SDL2::SDL2 glad::glad m
)

find_package(SDL2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(EGL QUIET)

if(APPLE)
    target_link_libraries(canim_gl PRIVATE "-framework OpenGL")
    set(canim_rpath "@loader_path")
elseif(UNIX)
    target_link_libraries(canim_gl PRIVATE OpenGL::GL EGL)
    set(canim_rpath "$ORIGIN")
else()
    message(FATAL_ERROR "Canim is not supported on Windows")
endif()

set_target_properties(canim canim_gl PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    BUILD_RPATH "${canim_rpath}"
    INSTALL_RPATH "${canim_rpath}"
)

install(TARGETS canim canim_gl
    LIBRARY DESTINATION lib
)
