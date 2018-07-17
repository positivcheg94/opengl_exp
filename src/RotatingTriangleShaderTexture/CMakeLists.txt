cmake_minimum_required(VERSION 2.8.12)

include_directories(include)
set(RotatingTriangleShaderTexture_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_executable(RotatingTriangleShaderTexture ${RotatingTriangleShaderTexture_sources})
target_link_libraries(RotatingTriangleShaderTexture glfw glad)

set_target_properties(RotatingTriangleShaderTexture PROPERTIES FOLDER Examples/)