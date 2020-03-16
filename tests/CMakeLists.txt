add_executable(test_add test_add.cpp)
target_link_libraries(test_add PRIVATE Catch2::Catch2 yala)
add_test(NAME TestAdd COMMAND test_add)
