cmake_minimum_required(VERSION 2.8.12)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(OpenGL_Learn)

# GLFW without tests
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
add_subdirectory(dependencies/glfw)

add_subdirectory(dependencies/glm)

include_directories(dependencies/glm)

# setup GLAD
file(COPY "${GLFW_SOURCE_DIR}/deps/glad/glad.h" DESTINATION "${CMAKE_BINARY_DIR}/additional_include/glad/")
file(COPY "${GLFW_SOURCE_DIR}/deps/KHR/khrplatform.h" DESTINATION "${CMAKE_BINARY_DIR}/additional_include/KHR/")
include_directories("${CMAKE_BINARY_DIR}/additional_include/")

add_library(glad "${GLFW_SOURCE_DIR}/deps/glad.c")
set_target_properties(glad PROPERTIES FOLDER Utilities/)

add_subdirectory(src)