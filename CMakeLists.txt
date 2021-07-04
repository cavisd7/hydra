cmake_minimum_required(VERSION 3.10)

project(sol VERSION 0.1)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")

add_subdirectory(deps/glfw)
add_subdirectory(deps/glad)

set(SOL-SRC src/main.cpp src/shader.cpp src/VertexBuffer.cpp src/IndexBuffer.cpp src/Renderer.h)
add_executable(sol ${SOL-SRC})
target_link_libraries(sol ${OPENGL_LIBRARIES} glfw glad)
