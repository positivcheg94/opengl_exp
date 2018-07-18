cmake_minimum_required(VERSION 2.8.12)

include_directories(include)
set(Tutorial1_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_executable(Tutorial1 ${Tutorial1_sources})
target_link_libraries(Tutorial1 glfw glad)

set_target_properties(Tutorial1 PROPERTIES FOLDER Tutorials/)