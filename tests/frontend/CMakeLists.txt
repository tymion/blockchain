add_executable(frontend_consolemenu_tests consolemenu_tests.cpp)
target_link_libraries(frontend_consolemenu_tests
    gmock
    gtest_main
    frontend
    headers
    test_headers
)
add_test(frontend_consolemenu_tests frontend_consolemenu_tests)

add_executable(frontend_menucontroller_tests menucontroller_tests.cpp)
target_link_libraries(frontend_menucontroller_tests
    gmock
    gtest_main
    frontend
    headers
    test_headers
)
add_test(frontend_menucontroller_tests frontend_menucontroller_tests)