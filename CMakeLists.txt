cmake_minimum_required(VERSION 4.2)
project(Youtube_opengl)

set(CMAKE_CXX_STANDARD 20)

add_executable(Youtube_opengl
        main.cpp
        "Source Files/glad.c"
        "Header Files/shaderclass.h"
        "Source Files/shaderclass.cpp"
        "Source Files/VBO.cpp"
        "Header Files/VBO.h"
        "Source Files/EBO.cpp"
        "Header Files/EBO.h"
        "Source Files/VAO.cpp"
        "Header Files/VAO.h"
        "Source Files/stb.cpp"
        "Header Files/Texture.h"

)

target_include_directories(Youtube_opengl PRIVATE
        "${CMAKE_SOURCE_DIR}/Libraries/Include"
        "${CMAKE_CURRENT_SOURCE_DIR}/Header Files"


)

target_link_libraries(Youtube_opengl
        ${CMAKE_SOURCE_DIR}/Libraries/Lib/libglfw3.a
        GL
        X11
        pthread
        dl
)