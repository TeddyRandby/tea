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
# find_package(Curses REQUIRED)

configure_file(TeaConfig.h.in TeaConfig.h)

add_executable(tests ../tests/all.cpp)
target_compile_features(tests PRIVATE
      cxx_std_20)

target_include_directories(tests PUBLIC
      "${PROJECT_BINARY_DIR}"
      "${GTEST_INCLUDE_DIR}")

target_link_libraries(tests
      PUBLIC "${GTEST_LIBRARIES}"
      PRIVATE Threads::Threads)
