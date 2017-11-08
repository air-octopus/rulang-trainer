cmake_minimum_required(VERSION 3.8)

project(rulang-trainer-lib)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        Trainer.h
        ExercisePool.h
        Exercise.h
        Student.h
        Admin.h
        LanguageRule.h
        )

set(SOURCE_FILES
        Trainer.cpp
        ExercisePool.cpp
        Exercise.cpp
        Student.cpp
        Admin.cpp
        LanguageRule.cpp
        )

add_library(${PROJECT_NAME} STATIC
        ${SOURCE_FILES} ${HEADER_FILES}
)