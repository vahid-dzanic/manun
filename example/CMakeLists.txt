cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(rpc VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(Boost REQUIRED COMPONENTS system)
if(NOT TARGET vdc::manun)
  find_package(manun REQUIRED)
endif()

add_executable(${PROJECT_NAME}
  src/Chat.cpp
  src/Client.cpp
  src/main.cpp
  src/mainwindow.cpp
  src/Server.cpp
  src/SineGenerator.cpp
  src/SineViewer.cpp
  src/Socket.cpp
  src/Chat.h
  src/ChatProtocol.h
  src/Client.h
  src/IEndpoint.h
  src/mainwindow.h
  src/Server.h
  src/SineGenerator.h
  src/SineProtocol.h
  src/SineViewer.h
  src/Socket.h
  src/mainwindow.ui
  src/SineGenerator.ui
  src/SineViewer.ui)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    vdc::manun
    Boost::system
    Qt5::Widgets
    pthread)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    VERSION "${PROJECT_VERSION}")

target_include_directories(${PROJECT_NAME}
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src)

target_compile_options(${PROJECT_NAME}
  PRIVATE
    $<$<STREQUAL:"${CMAKE_BUILD_TYPE}","Release">:-Werror>
    $<$<STREQUAL:"${CMAKE_BUILD_TYPE}","Release">:-O3>
    -Wall
    -Wextra
    -pedantic
    $<$<BOOL:${CMAKE_COMPILER_IS_CLANGCXX}>:-Weverything>)
