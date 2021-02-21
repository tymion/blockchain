add_library(frontend menucontroller.cpp)

target_link_libraries(frontend PUBLIC asio)

set_target_properties(frontend PROPERTIES CXX_CLANG_TIDY clang-tidy-10)
