
#ENV vars
set(CMAKE_EXPORT_COMIPLE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.10)
project(Test VERSION 1.0)

#Curses is needed for ASCII terminal stuff.
find_package(Curses REQUIRED)

configure_file(TestConfig.h.in TestConfig.h)

add_executable(Test nctest.cpp)

target_include_directories(Test PUBLIC
      "${PROJECT_BINARY_DIR}"
      "${CURSES_INCLUDE_DIR}")

target_link_libraries(Test 
      "${CURSES_LIBRARIES}")


