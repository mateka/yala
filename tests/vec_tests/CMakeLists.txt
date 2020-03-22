add_executable(
    vec_tests
    vec_tests.cpp
    vec1_tests.cpp
    vec2_tests.cpp
    vec3_tests.cpp
    vec4_tests.cpp
)
target_link_libraries(vec_tests PRIVATE Catch2::Catch2 yala)
add_test(NAME TestVec COMMAND vec_tests)
