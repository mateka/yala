add_executable(matrix_tests matrix_tests.cpp)
target_link_libraries(matrix_tests PRIVATE Catch2::Catch2 yala)
add_test(NAME TestMatrix COMMAND matrix_tests)
