# tests/CMakeLists.txt
find_package(cmocka CONFIG REQUIRED)

add_executable(canim_vec_tests test_vec.c)
target_link_libraries(canim_vec_tests PRIVATE canim cmocka::cmocka)
target_include_directories(canim_vec_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
add_test(
    NAME Canim_Vec_Tests
    COMMAND canim_vec_tests
)

add_executable(canim_da_tests test_da.c)
target_link_libraries(canim_da_tests PRIVATE canim cmocka::cmocka)
target_include_directories(canim_da_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_test(
    NAME Canim_Da_Tests
    COMMAND canim_da_tests
)
