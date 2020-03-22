add_executable(
    normal_tests
    normal_tests.cpp
    normal1_tests.cpp
    normal2_tests.cpp
    normal3_tests.cpp
    normal4_tests.cpp
)
target_link_libraries(normal_tests PRIVATE Catch2::Catch2 yala)
add_test(NAME TestNormal COMMAND normal_tests)
