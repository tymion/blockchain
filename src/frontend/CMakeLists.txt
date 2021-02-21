add_library(frontend INTERFACE)

target_link_libraries(frontend INTERFACE asio)

set_target_properties(io PROPERTIES CXX_CLANG_TIDY clang-tidy-10)
