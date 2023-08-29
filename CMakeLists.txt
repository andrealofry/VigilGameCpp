cmake_minimum_required(VERSION 3.26)
project(VigilGameCpp)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenGL REQUIRED)

#target_link_libraries(
#        GLUT::GLUT
#        GLEW::GLEW
#)

if (APPLE)
    include_directories(/opt/homebrew/include)
endif (APPLE)

add_executable(VigilGameCpp src/main.cpp
        src/Renderer.cpp
        src/Renderer.h
        src/debugbreak.h)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/res
        ${PROJECT_BINARY_DIR}/res
        COMMENT "Copyng resources into binary directory")

add_dependencies(VigilGameCpp copy_resources)

#if(UNIX AND NOT APPLE)
#    set(LINUX TRUE)
#endif()
#if (LINUX)
target_link_libraries(VigilGameCpp GL GLU glut GLEW glfw X11 Xxf86vm Xrandr pthread Xi dl)
#endif (LINUX)
#if (APPLE)
#    target_link_libraries(VigilGameCpp glfw3 "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
#endif (APPLE)

add_definitions(-DGLEW_STATIC)