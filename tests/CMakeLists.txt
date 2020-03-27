add_subdirectory(vec_tests)
add_subdirectory(normal_tests)
add_subdirectory(matrix_tests)


add_executable(constexpr_math_tests constexpr_math_tests.cpp)
target_link_libraries(constexpr_math_tests PRIVATE Catch2::Catch2 yala)
add_test(NAME TestConstexprMath COMMAND constexpr_math_tests)

add_executable(matrix_vector_tests matrix_vector_tests.cpp)
target_link_libraries(matrix_vector_tests PRIVATE Catch2::Catch2 yala)
add_test(NAME TestMatrixVector COMMAND matrix_vector_tests)
