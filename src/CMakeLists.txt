# src/CMakeLists.txt
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

find_package(unofficial-libmupdf CONFIG REQUIRED)

add_library(canim SHARED
    ${CANIM_CORE_SRC}
)

add_library(canim::canim ALIAS canim)

target_compile_definitions(canim
    PUBLIC
        CANIM_BUILD
        $<$<CONFIG:Debug>:CANIM_DEBUG>
        $<$<NOT:$<CONFIG:Debug>>:CANIM_RELEASE>
)

target_include_directories(canim
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(canim
    PRIVATE
        m
        unofficial::libmupdf::libmupdf
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(EGL QUIET)

add_library(canim_gl SHARED
    gfx/gl.c
)

add_library(canim::canim_gl ALIAS canim_gl)

target_compile_definitions(canim_gl
    PUBLIC
        CANIM_BUILD
        $<$<CONFIG:Debug>:CANIM_DEBUG>
        $<$<NOT:$<CONFIG:Debug>>:CANIM_RELEASE>
)

target_include_directories(canim_gl
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(canim_gl
    PUBLIC
        canim::canim
    PRIVATE
        PkgConfig::SDL2
        glad::glad
        m
)

if(APPLE)
    target_link_libraries(canim_gl
        PRIVATE
            "-framework OpenGL"
    )

    set(canim_rpath "@loader_path")
elseif(UNIX AND NOT APPLE)
    target_link_libraries(canim_gl
        PRIVATE
            OpenGL::GL
    )

    if(TARGET EGL::EGL)
        target_link_libraries(canim_gl PRIVATE EGL::EGL)
    elseif(EGL_FOUND)
        target_link_libraries(canim_gl PRIVATE EGL)
    else()
        message(WARNING "EGL was not found; continuing without explicit EGL linkage")
    endif()

    set(canim_rpath "$ORIGIN")
else()
    message(FATAL_ERROR "canim is not supported on this platform")
endif()

set_target_properties(canim canim_gl PROPERTIES
    OUTPUT_NAME canim
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    BUILD_RPATH "${canim_rpath}"
    INSTALL_RPATH "${canim_rpath}"
)

set_target_properties(canim_gl PROPERTIES
    OUTPUT_NAME canim_gl
)

install(TARGETS canim canim_gl
    EXPORT canimTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    EXPORT canimTargets
    NAMESPACE canim::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/canim
)
