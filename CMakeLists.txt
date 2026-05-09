# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(canim
    VERSION 1.0.0
    LANGUAGES C
)

if(WIN32)
    message(FATAL_ERROR "canim is not supported on Windows")
endif()

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/canimConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/canimConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/canim
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/canimConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/canimConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/canimConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/canim
)
