cmake_minimum_required(VERSION 3.16)

project(UDEMY_OpenGL_Course)

add_executable(${PROJECT_NAME} source/main.cpp)

find_package(GLEW REQUIRED)

include_directories("source/External_Libs/GLM")

target_link_libraries(${PROJECT_NAME} GL GLEW::GLEW glfw)