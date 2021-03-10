add_executable(blockchainservice_tests blockchainservice_tests.cpp)
target_link_libraries(blockchainservice_tests
    gmock
    gtest_main
    backend
    dal
    crypto_dummy
    headers
)
add_test(backend_blockchainservice_tests blockchainservice_tests)
#set_target_properties(backend_blockchainservice_tests PROPERTIES CXX_CLANG_TIDY clang-tidy-10)