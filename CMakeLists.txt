cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(manun VERSION 1.0.0)

find_package(stdex REQUIRED)

set(HEADER_FILES
  include/manun/converter_factory.h
  include/manun/convert.h
  include/manun/convert_proxy.h
  include/manun/function_map.h
  include/manun/manun_exceptions.h
  include/manun/std_type_converter.h
  include/manun/type_name_map.h
  include/manun/utilities.h)

add_library(${PROJECT_NAME} SHARED
  src/converter_factory.cpp
  src/function_map.cpp
  src/manun_exceptions.cpp
  src/type_name_map.cpp
  src/utilities.cpp)
add_library(chili::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    chili::stdex)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    PUBLIC_HEADER "${HEADER_FILES}"
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}")

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    src)

target_compile_options(${PROJECT_NAME}
  PUBLIC
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
#    -Wno-variadic-macros
#    -Wno-gnu-zero-variadic-macro-arguments
  PRIVATE
    -Werror
    -Wall
    -Wextra
    $<$<BOOL:${CMAKE_COMPILER_IS_CLANGCXX}>:-Weverything>)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-config
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  PUBLIC_HEADER DESTINATION include/${PROJECT_NAME})
install(EXPORT ${PROJECT_NAME}-config NAMESPACE chili:: DESTINATION cmake)

enable_testing()
add_subdirectory(test)
