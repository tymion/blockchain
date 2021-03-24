add_executable(consolemenuview_tests consolemenuview_tests.cpp)
target_link_libraries(consolemenuview_tests
    gmock
    gtest_main
    frontend
    headers
)
add_test(frontend_consolemenuview_tests consolemenuview_tests)
#set_target_properties(frontend_consolemenu_tests PROPERTIES CXX_CLANG_TIDY clang-tidy-10)

add_executable(menucontroller_tests menucontroller_tests.cpp)
target_link_libraries(menucontroller_tests
    gmock
    gtest_main
    frontend
    headers
)
add_test(frontend_menucontroller_tests menucontroller_tests)
#set_target_properties(frontend_menucontroller_tests PROPERTIES CXX_CLANG_TIDY clang-tidy-10)