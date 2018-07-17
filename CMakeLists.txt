cmake_minimum_required(VERSION 2.8.12)

project(OpenGL_Learn)

# GLFW without tests
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
add_subdirectory(dependencies/glfw)

# setup GLAD
file(COPY "${GLFW_SOURCE_DIR}/deps/glad/glad.h" DESTINATION "${PROJECT_SOURCE_DIR}/additional_include/")
include_directories("${PROJECT_SOURCE_DIR}/additional_include/glad/")


add_subdirectory(src)