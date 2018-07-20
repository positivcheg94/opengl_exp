cmake_minimum_required(VERSION 3.4.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(OpenGL_Learn)

add_subdirectory(dependencies)

# setup GLAD
file(COPY "${GLFW_SOURCE_DIR}/deps/glad/glad.h" DESTINATION "${CMAKE_BINARY_DIR}/additional_include/glad/")
file(COPY "${GLFW_SOURCE_DIR}/deps/KHR/khrplatform.h" DESTINATION "${CMAKE_BINARY_DIR}/additional_include/KHR/")

include_directories(dependencies/glm)

include_directories("include/")
include_directories("${CMAKE_BINARY_DIR}/additional_include/")

add_library(glad "${GLFW_SOURCE_DIR}/deps/glad.c")
set_target_properties(glad PROPERTIES FOLDER Utilities/)

add_subdirectory(src)