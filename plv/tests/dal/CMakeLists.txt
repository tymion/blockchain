add_executable(chunkiterator_tests chunkiterator_tests.cpp)
target_link_libraries(chunkiterator_tests
    gmock
    gtest_main
    dal
    io
    headers
)
add_test(dal_chunkiterator_tests chunkiterator_tests)
#set_target_properties(dal_chunkiterator_tests PROPERTIES CXX_CLANG_TIDY clang-tidy-10)

add_executable(blockchainstorage_tests blockchainstorage_tests.cpp)
target_link_libraries(blockchainstorage_tests
    gmock
    gtest_main
    dal
    io
    headers
)
add_test(dal_blockchainstorage_tests blockchainstorage_tests)
#set_target_properties(dal_blockchainstorage_tests PROPERTIES CXX_CLANG_TIDY clang-tidy-10)

add_executable(blockparser_tests blockparser_tests.cpp)
target_link_libraries(blockparser_tests
    gmock
    gtest_main
    dal
    headers
    fmt
)
add_test(dal_blockparser_tests blockparser_tests)
#set_target_properties(dal_blockparser_tests PROPERTIES CXX_CLANG_TIDY clang-tidy-10)