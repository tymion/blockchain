cmake_minimum_required(VERSION 3.15)

cmake_policy(SET CMP0091 NEW)

project(blockchain)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -ftest-coverage -fcoverage-mapping -fcoroutines-ts  -stdlib=libc++ -DASIO_DISABLE_STD_COROUTINE=1 -pthread")
set(GSL_CXX_STANDARD 20)

include(CTest)

set(ASIO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/asio)

add_library(headers INTERFACE)
target_include_directories(headers
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(ext/googletest EXCLUDE_FROM_ALL)
add_subdirectory(ext/fmt EXCLUDE_FROM_ALL)
add_subdirectory(ext/GSL EXCLUDE_FROM_ALL)

add_subdirectory(plv/asio-cmake)
add_subdirectory(plv/io)
add_subdirectory(plv/serializers)
add_subdirectory(plv/dal)
add_subdirectory(plv/crypto)
add_subdirectory(plv/backend)
add_subdirectory(plv/frontend)
add_subdirectory(plv/tests)
