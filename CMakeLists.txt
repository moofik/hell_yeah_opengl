cmake_minimum_required(VERSION 3.22)
project(opengl1)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-ldl -lGL -lX11 -lpthread -lXrandr -lXi")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(GLFW_INCLUDE_DIRS "/usr/include/")

add_executable(opengl1 main.cpp glad.c shader.h window.h utils/debug.h utils/default.h utils/stb_image.cpp camera.cpp camera.h shader.cpp window.cpp)

target_include_directories(opengl1 PUBLIC ${GLFW_INCLUDE_DIRS})
target_link_libraries(opengl1 "/usr/lib/x86_64-linux-gnu/libglfw.so" -ldl)
