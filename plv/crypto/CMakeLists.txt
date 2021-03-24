add_library(crypto_dummy STATIC dummy.cpp)
target_link_libraries(crypto_dummy headers)

#set_target_properties(crypto_dummy PROPERTIES CXX_CLANG_TIDY clang-tidy-10)