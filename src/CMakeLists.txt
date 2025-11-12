cmake_minimum_required(VERSION 3.10)
project(CanimSources LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

set(GFX_SRC "")
set(CANIM_SRC "")
foreach(FILE ${ALL_SRC})
  if(FILE MATCHES "/gfx/")
    list(APPEND GFX_SRC ${FILE})
  else()
    list(APPEND CANIM_SRC ${FILE})
  endif()
endforeach()

add_library(canim SHARED ${CANIM_SRC})
target_include_directories(canim PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(canim PRIVATE m)

foreach(GFX_FILE ${GFX_SRC})
  get_filename_component(NAME ${GFX_FILE} NAME_WE)
  add_library(${NAME} SHARED ${GFX_FILE})
  target_include_directories(${NAME} PUBLIC
      $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:include>
  )
  target_link_libraries(${NAME} PRIVATE SDL2 EGL GL m)
  set_target_properties(${NAME} PROPERTIES
      OUTPUT_NAME "${NAME}"
      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/canim"
  )
endforeach()

install(TARGETS canim
    LIBRARY DESTINATION lib/canim
)

foreach(GFX_FILE ${GFX_SRC})
  get_filename_component(NAME ${GFX_FILE} NAME_WE)
  install(TARGETS ${NAME}
      LIBRARY DESTINATION lib/canim
  )
endforeach()

