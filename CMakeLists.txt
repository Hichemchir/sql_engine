# To generate build files w/ CMake: cd build && cmake ..
# To compile the project & run: cmake --build . && ./sql_engine

cmake_minimum_required(VERSION 3.10)
project(minimal_sql_engine VERSION 0.5.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

# ============================================================================
# LIBRARY: shared code between main & tests
# ============================================================================

set(LIB_SOURCES
    src/storage/table.cpp
    src/storage/catalog.cpp
    src/parser/token.cpp
    src/parser/lexer.cpp
)

add_library(sql_engine_lib STATIC ${LIB_SOURCES})

# ============================================================================
# MAIN EXECUTABLE
# ============================================================================

add_executable(sql_engine src/main.cpp)
target_link_libraries(sql_engine sql_engine_lib)

# ============================================================================
# GOOGLE TEST SETUP
# ============================================================================

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ============================================================================
# TEST EXECUTABLES
# ============================================================================

# Test Lexer
add_executable(test_lexer tests/test_lexer.cpp)
target_link_libraries(test_lexer sql_engine_lib GTest::gtest_main)

# Test Table
add_executable(test_table tests/test_table.cpp)
target_link_libraries(test_table sql_engine_lib GTest::gtest_main)

# Test Catalog
add_executable(test_catalog tests/test_catalog.cpp)
target_link_libraries(test_catalog sql_engine_lib GTest::gtest_main)

# ============================================================================
# REGISTER TESTS WITH CTEST
# ============================================================================

include(GoogleTest)
gtest_discover_tests(test_lexer)
gtest_discover_tests(test_table)
gtest_discover_tests(test_catalog)