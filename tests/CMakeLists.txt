# tests/CMakeLists.txt
find_package(cmocka CONFIG REQUIRED)

add_executable(canim_vec_tests
    test_vec.c
)

target_link_libraries(canim_vec_tests
    PRIVATE
        canim::canim
        cmocka::cmocka
)

add_test(
    NAME canim_vec_tests
    COMMAND canim_vec_tests
)

add_executable(canim_da_tests
    test_da.c
)

target_link_libraries(canim_da_tests
    PRIVATE
        canim::canim
        cmocka::cmocka
)

add_test(
    NAME canim_da_tests
    COMMAND canim_da_tests
)
