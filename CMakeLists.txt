cmake_minimum_required(VERSION 3.26)

project(lab1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED)

# Download glad/glfw at configure time

add_executable(program
  "src/lab1.cpp"
  "glad/src/glad.c"
   "src/ShaderClass.hpp" "src/ShaderClass.cpp")

find_package(OpenGL REQUIRED)
add_subdirectory("glfw-3.3.8")

target_include_directories(program PUBLIC
  ${OPENGL_INCLUDE_DIRS}
  "glad/include"
  )
target_link_libraries(program
  glfw
  ${OPENGL_LIBRARIES}
  )
