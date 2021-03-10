add_library(io consolereadwriter.cpp)

target_link_libraries(io PUBLIC asio)

#set_target_properties(io PROPERTIES CXX_CLANG_TIDY clang-tidy-10)
