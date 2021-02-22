add_library(backend INTERFACE)

target_link_libraries(backend INTERFACE asio)

#set_target_properties(io PROPERTIES CXX_CLANG_TIDY clang-tidy-10)
