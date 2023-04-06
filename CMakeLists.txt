cmake_minimum_required(VERSION 3.26)

project(lab1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED)

# Download glad/glfw at configure time

add_executable(program
  "src/lab1.cpp"
  "glad/src/glad.c"
   "src/ShaderClass.hpp" "src/ShaderClass.cpp"
   "src/stb_image.cpp"
   "src/camera.cpp"
    "src/rVectorClass.cpp")

find_package(OpenGL REQUIRED)
add_subdirectory("glfw-3.3.8")
add_subdirectory("glm")

target_include_directories(program PUBLIC
  ${OPENGL_INCLUDE_DIRS}
  "glad/include"
  )
target_link_libraries(program
  glfw
  glm
  ${OPENGL_LIBRARIES}
  )
