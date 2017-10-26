cmake_minimum_required(VERSION 3.8)
project(trainer)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        Trainer.h
        ExercisePool.h
        Exercise.h
)

set(SOURCE_FILES
        Trainer.cpp
        ExercisePool.cpp
        Exercise.cpp
)

add_library(lib STATIC ${SOURCE_FILES} ${HEADER_FILES})