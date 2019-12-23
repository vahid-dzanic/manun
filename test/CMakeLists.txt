cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

find_package(GTest REQUIRED)

add_executable(fast_manun
  src/test_manun.cpp
  src/test_manun_functions.cpp)

target_link_libraries(fast_manun
  PRIVATE
    manun
    gtest
    gmock
    gtest_main
    pthread)

target_compile_options(fast_manun
  PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
    -Werror
    -Wall
    -Wextra
    $<$<BOOL:${CMAKE_COMPILER_IS_CLANGCXX}>:-Weverything>)

add_test(fast_manun fast_manun)
