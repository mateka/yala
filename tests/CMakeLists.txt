add_subdirectory(vec_tests)
add_subdirectory(normal_tests)
add_subdirectory(matrix_tests)


add_executable(constexpr_math_tests constexpr_math_tests.cpp)
target_link_libraries(constexpr_math_tests PRIVATE Catch2::Catch2 yala)
add_test(NAME TestConstexprMath COMMAND constexpr_math_tests)
