add_executable(netstring_tests netstring_tests.cpp)
target_link_libraries(netstring_tests
    gmock
    gtest_main
    serializers
    headers
)
add_test(serializers_netstring_tests netstring_tests)
#set_target_properties(serializers_netstring_tests PROPERTIES CXX_CLANG_TIDY clang-tidy-10)