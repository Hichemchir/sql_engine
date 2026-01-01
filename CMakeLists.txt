cmake_minimum_required(VERSION 3.10)

project(minimal_sql_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/**/*.h")

add_executable(sql_engine ${SOURCES} ${HEADERS})

enable_testing()
add_subdirectory(tests)