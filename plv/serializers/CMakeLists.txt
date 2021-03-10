add_library(serializers INTERFACE)

target_link_libraries(serializers INTERFACE GSL fmt)

#set_target_properties(serializers PROPERTIES CXX_CLANG_TIDY clang-tidy-10)
