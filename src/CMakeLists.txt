set(CANIM_CORE_SRC
    core/endian.c
    loader/loader.c
    io/utils.c
    io/ffmpeg.c
    io/screen.c
    math/utils.c
    math/vector.c
    math/quat.c
    log/log.c
    data/da.c
)

find_package(SDL2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED COMPONENTS OpenGL EGL)
find_package(unofficial-libmupdf CONFIG REQUIRED)

add_library(canim SHARED
    ${CANIM_CORE_SRC}
)

target_compile_definitions(canim
    PRIVATE
        CANIM_BUILD
    PUBLIC
        $<$<CONFIG:Debug>:CANIM_DEBUG>
        $<$<NOT:$<CONFIG:Debug>>:CANIM_RELEASE>
)

target_include_directories(canim
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(canim
    PRIVATE
        unofficial::libmupdf::libmupdf
)

if(UNIX AND NOT APPLE)
    target_link_libraries(canim PRIVATE m)
endif()

add_library(canim_gl SHARED
    gfx/gl.c
)

target_compile_definitions(canim_gl
    PRIVATE
        CANIM_BUILD
    PUBLIC
        $<$<CONFIG:Debug>:CANIM_DEBUG>
        $<$<NOT:$<CONFIG:Debug>>:CANIM_RELEASE>
)

target_link_libraries(canim_gl
    PUBLIC
        canim
    PRIVATE
        SDL2::SDL2
        glad::glad
)

if(APPLE)
    target_link_libraries(canim_gl
        PRIVATE
            "-framework OpenGL"
    )

    set(canim_rpath "@loader_path")
elseif(UNIX)
    target_link_libraries(canim_gl
        PRIVATE
            OpenGL::OpenGL
            OpenGL::EGL
            m
    )

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

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
    DESTINATION include
)
