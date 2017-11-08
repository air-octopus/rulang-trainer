cmake_minimum_required(VERSION 3.8)
project(rulang-trainer)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src/rulang_trainer_lib)

add_subdirectory(src/rulang_trainer_app)

add_subdirectory(src/third_party_supply)

add_subdirectory(third_party/sqlitepp)