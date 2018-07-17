cmake_minimum_required(VERSION 2.8.12)

include_directories(include)
set(Simple1_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_executable(Simple1 ${Simple1_sources})