cmake_minimum_required(VERSION 3.10)
project(Test VERSION 1.0)

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

add_executable(Sandbox
      TSandbox.cpp)

add_executable(Tests 
      ../tests/TComponentSuite.cpp
      ../tests/TApplicationSuite.cpp
      ../tests/TVec2Suite.cpp
      ../tests/TContentSuite.cpp)

target_compile_features(Tests 
      PRIVATE
      cxx_std_20)

target_compile_features(Sandbox 
      PRIVATE
      cxx_std_20)

target_include_directories(Tests 
      PUBLIC
      "${PROJECT_SOURCE_DIR}/src"
      "${PROJECT_BINARY_DIR}"
      "${GTEST_INCLUDE_DIR}"
      "${CURSES_INCLUDE_DIR}"
      )

target_include_directories(Sandbox 
      PUBLIC
      "${PROJECT_SOURCE_DIR}/src"
      "${PROJECT_BINARY_DIR}"
      "${CURSES_INCLUDE_DIR}"
      )

target_link_libraries(Sandbox
      PUBLIC 
      "${CURSES_LIBRARIES}")

target_link_libraries(Tests
      PUBLIC 
      "${GTEST_LIBRARIES}"
      "${GTEST_MAIN_LIBRARIES}"
      "${CURSES_LIBRARIES}"
      PRIVATE 
      Threads::Threads)
