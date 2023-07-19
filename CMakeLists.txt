cmake_minimum_required(VERSION 3.10)
project(siltstone-gl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(siltstone-gl main.cpp thirdparty/src/pugixml.cpp)
target_link_libraries(siltstone-gl PUBLIC GLEW glfw GL assimp)
target_include_directories(siltstone-gl PUBLIC include thirdparty/include)
