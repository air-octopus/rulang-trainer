cmake_minimum_required(VERSION 2.8.12)

project(rulang-trainer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

set(HEADER_FILES
)

set(SOURCE_FILES
        main.cpp
        qml.qrc
)

add_executable(${PROJECT_NAME}
        ${HEADER_FILES} ${SOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Quick
)
