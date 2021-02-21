add_executable(io_consolereadwriter_tests consolereadwriter_tests.cpp)
target_link_libraries(io_consolereadwriter_tests
    gmock
    gtest_main
    io
    headers
    test_headers
)
add_test(io_consolereadwriter_tests io_consolereadwriter_tests)
set_target_properties(io_consolereadwriter_tests PROPERTIES CXX_CLANG_TIDY clang-tidy-10)