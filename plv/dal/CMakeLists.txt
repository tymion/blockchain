add_library(dal INTERFACE)

target_link_libraries(dal INTERFACE GSL fmt serializers)

#set_target_properties(io PROPERTIES CXX_CLANG_TIDY clang-tidy-10)
