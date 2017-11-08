cmake_minimum_required(VERSION 3.8)

project(third-party-supply)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        sqlitepp_helper.hpp
        utf8_helper.hpp
)

add_library(${PROJECT_NAME} INTERFACE
        ${HEADER_FILES}
)