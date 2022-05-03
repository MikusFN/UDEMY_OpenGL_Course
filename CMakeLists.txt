cmake_minimum_required(VERSION 3.16)

project(UDEMY_OpenGL_Course)

include_directories(${PROJECT_NAME} source/External_Libs/GLM/)
include_directories(${PROJECT_NAME} source/Public/)

add_executable(${PROJECT_NAME} source/main.cpp source/Private/Mesh.cpp source/Private/Shader.cpp)

find_package(GLEW REQUIRED)

target_link_libraries(${PROJECT_NAME} GL GLEW::GLEW glfw)
