if(NOT EXISTS ${ASIO_DIR})
    message(FATAL_ERROR "ASIO_DIR is empty. Please define path to asio library.")
endif()

add_library(asio ${ASIO_DIR}/asio/src/asio.cpp)

target_include_directories(asio
    PUBLIC
    ${ASIO_DIR}/asio/include
)

target_compile_definitions(asio
    PUBLIC
    ASIO_SEPARATE_COMPILATION
    ASIO_ENABLE_CANCELIO
    ASIO_NO_DEPRECATED
)