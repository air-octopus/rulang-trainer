cmake_minimum_required(VERSION 2.8.11)

# Set project name
project(utf8)

set(HEADER_FILES
        utf8/checked.h
        utf8/core.h
        utf8/unchecked.h
        utf8.h
        )

add_library(
        ${PROJECT_NAME} INTERFACE
        )
