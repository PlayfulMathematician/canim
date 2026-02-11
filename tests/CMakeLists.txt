find_package(cmocka CONFIG REQUIRED)

add_executable(canim_tests test_vec.c)
target_link_libraries(canim_tests PRIVATE canim cmocka::cmocka)
target_include_directories(canim_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
add_test(
    NAME Canim_Unit_Tests
    COMMAND canim_tests
)
