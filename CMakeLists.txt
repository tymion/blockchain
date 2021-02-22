cmake_minimum_required(VERSION 3.15)

cmake_policy(SET CMP0091 NEW)

project(blockchain)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines-ts  -stdlib=libc++ -DASIO_DISABLE_STD_COROUTINE=1 -pthread")
set(GSL_CXX_STANDARD 20)

include(CTest)

set(ASIO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/asio)

add_library(headers INTERFACE)
target_include_directories(headers
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(test_headers INTERFACE)
target_include_directories(headers
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
)

add_subdirectory(ext/googletest EXCLUDE_FROM_ALL)

add_subdirectory(src/asio-cmake)
add_subdirectory(src/io)
add_subdirectory(src/frontend)
add_subdirectory(src/backend)
add_subdirectory(tests)
