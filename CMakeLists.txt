cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME Scene3D)
project(${PROJECT_NAME})



set(GRAPHIC src/graphics/Shader.hpp
			src/graphics/Shader.cpp
			src/graphics/Mesh.hpp
			src/graphics/Mesh.cpp
			src/graphics/Vertex.hpp)



set(RESOURCES res/shader.vert
			  res/shader.frag)


find_package(GLEW REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)


add_executable(${PROJECT_NAME} src/main.cpp ${RESOURCES} ${GRAPHIC})
target_link_libraries(${PROJECT_NAME} GLEW::GLEW sfml-graphics sfml-window)