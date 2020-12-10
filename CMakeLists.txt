cmake_minimum_required(VERSION 3.10)
project(Tea LANGUAGES CXX VERSION 1.0)

#ENV vars
set(CMAKE_EXPORT_COMIPLE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Required for testing
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)
find_package(GTest)

# Required for application
find_package(Curses REQUIRED)

configure_file(TeaConfig.h.in TeaConfig.h)

add_library(screen
      ../src/tea/screen/TScreen.hpp
      ../src/tea/screen/TBorder.cpp
      ../src/tea/screen/THeader.cpp
      ../src/tea/screen/TBody.cpp)

add_library(component
      ../src/tea/component/TComponent.hpp
      ../src/tea/component/TApplication.hpp
      ../src/tea/component/TContent.hpp)

set_target_properties(component PROPERTIES LINKER_LANGUAGE CXX)

add_library(utils
      ../src/tea/utils/TVec2.hpp)

set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)

add_library(tea::screen ALIAS screen)
add_library(tea::component ALIAS component)
add_library(tea::utils ALIAS utils)

target_link_libraries(component 
      PUBLIC 
      utils)

target_link_libraries(screen
      PUBLIC
      component
      curses)

add_executable(sandbox
      TSandbox.cpp)

add_executable(tests 
      ../tests/TComponentSuite.cpp
      ../tests/TApplicationSuite.cpp
      ../tests/TVec2Suite.cpp
      ../tests/TContentSuite.cpp)

target_compile_features(tests 
      PRIVATE
      cxx_std_20)

target_compile_features(sandbox 
      PRIVATE
      cxx_std_20)

target_include_directories(tests 
      PUBLIC
      src)

target_include_directories(sandbox 
      PUBLIC
      src)

target_link_libraries(sandbox
      PRIVATE 
      screen
      curses)

target_link_libraries(tests
      PRIVATE 
      gtest
      gtest_main
      curses
      screen
      Threads::Threads)
