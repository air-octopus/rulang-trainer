cmake_minimum_required(VERSION 2.8.11)

# Set project name
project(sqlite3)

set(HEADER_FILES
        sqlite3.h
        sqlite3ext.h
        )

set(SOURCE_FILES
        sqlite3.c
        )

add_library(
        ${PROJECT_NAME}
        ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC -ldl)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "third_party/sqlite")