cmake_minimum_required(VERSION 3.10)
project(CanimSources LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# --- All .c files under src ---
file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

# --- Split gfx and non-gfx files ---
set(GFX_SRC "")
set(CANIM_SRC "")

foreach(FILE ${ALL_SRC})
  if (FILE MATCHES "/gfx/")
    list(APPEND GFX_SRC ${FILE})
  else()
    list(APPEND CANIM_SRC ${FILE})
  endif()
endforeach()

# --- Build main library (everything except gfx) ---
add_library(canim SHARED ${CANIM_SRC})
target_include_directories(canim PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(canim PRIVATE m)

# --- Build each gfx backend as its own .so ---
foreach(GFX_FILE ${GFX_SRC})
  get_filename_component(NAME ${GFX_FILE} NAME_WE)
  add_library(${NAME} SHARED ${GFX_FILE})
  target_include_directories(${NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
  target_link_libraries(${NAME} PRIVATE m)
  set_target_properties(${NAME} PROPERTIES
        OUTPUT_NAME "${NAME}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/canim"
    )
endforeach()

