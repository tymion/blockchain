add_executable(backend_netstring_tests netstring_tests.cpp)
target_link_libraries(backend_netstring_tests
    gmock
    gtest_main
    backend
    headers
    test_headers
)
add_test(backend_netstring_tests backend_netstring_tests)
set_target_properties(backend_netstring_tests PROPERTIES CXX_CLANG_TIDY clang-tidy-10)

add_executable(backend_chunkiterator_tests chunkiterator_tests.cpp)
target_link_libraries(backend_chunkiterator_tests
    gmock
    gtest_main
    backend
    io
    headers
    test_headers
)
add_test(backend_chunkiterator_tests backend_chunkiterator_tests)
set_target_properties(backend_chunkiterator_tests PROPERTIES CXX_CLANG_TIDY clang-tidy-10)

add_executable(backend_blockchainstorage_tests blockchainstorage_tests.cpp)
target_link_libraries(backend_blockchainstorage_tests
    gmock
    gtest_main
    backend
    io
    headers
    test_headers
)
add_test(backend_blockchainstorage_tests backend_blockchainstorage_tests)
set_target_properties(backend_blockchainstorage_tests PROPERTIES CXX_CLANG_TIDY clang-tidy-10)