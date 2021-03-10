add_library(frontend menucontroller.cpp)

target_link_libraries(frontend PUBLIC asio headers fmt)

#set_target_properties(frontend PROPERTIES CXX_CLANG_TIDY clang-tidy-10)

#add_executable(blockchain main.cpp)

#target_link_libraries(blockchain PUBLIC asio backend frontend io headers)

#set_target_properties(blockchain PROPERTIES CXX_CLANG_TIDY clang-tidy-10)
