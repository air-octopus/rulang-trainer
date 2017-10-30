cmake_minimum_required(VERSION 2.8.11)

add_subdirectory(sqlite)

# Compile as C++14
SET(CMAKE_CXX_STANDARD 14)

# Set project name
project(sqlitepp)

set(HEADER_FILES
        sqlitepp/binders.hpp
        sqlitepp/converters.hpp
        sqlitepp/exception.hpp
        sqlitepp/into.hpp
        sqlitepp/query.hpp
        sqlitepp/session.hpp
        sqlitepp/sqlitepp.hpp
        sqlitepp/statement.hpp
        sqlitepp/string.hpp
        sqlitepp/transaction.hpp
        sqlitepp/unicode.hpp
        sqlitepp/use.hpp
        )

set(SOURCE_FILES
        sqlitepp/exception.cpp
        sqlitepp/query.cpp
        sqlitepp/session.cpp
        sqlitepp/statement.cpp
        sqlitepp/string.cpp
        sqlitepp/transaction.cpp
        )

add_library(
        ${PROJECT_NAME}
        ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
        PUBLIC sqlite3)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "third_party/sqlite")