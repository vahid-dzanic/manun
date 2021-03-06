cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(manun VERSION 1.0.0 LANGUAGES CXX)

find_package(stdex REQUIRED)

set(HEADER_FILES
  include/manun/converter_factory.h
  include/manun/convert.h
  include/manun/convert_proxy.h
  include/manun/function_map.h
  include/manun/includes
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
add_library(vdc::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    vdc::stdex)

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

target_compile_features(${PROJECT_NAME}
  PUBLIC
    cxx_std_17)

target_compile_options(${PROJECT_NAME}
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
configure_file(${PROJECT_SOURCE_DIR}/config/config.cmake ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake @ONLY)
install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake DESTINATION cmake)

# init variables if not defined
if(NOT DEFINED MANUN_BUILD_WITH_EXAMPLE)
  set(MANUN_BUILD_WITH_EXAMPLE ON)
endif()
if(NOT DEFINED MANUN_BUILD_WITH_TESTS)
  set(MANUN_BUILD_WITH_TESTS ON)
endif()

if (${MANUN_BUILD_WITH_EXAMPLE})
  add_subdirectory(example)
endif()
if (${MANUN_BUILD_WITH_TESTS})
  enable_testing()
  add_subdirectory(test)
endif()
