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
    link_directories(/opt/homebrew/Cellar/glfw/3.3.8/lib /opt/homebrew/Cellar/glew/2.2.0_1/lib/)

endif (APPLE)

add_executable(VigilGameCpp src/main.cpp
        src/Renderer.cpp
        src/Renderer.h
        src/debugbreak.h
        src/VertexBuffer.cpp
        src/VertexBuffer.h
        src/IndexBuffer.cpp
        src/IndexBuffer.h
        src/VertexArray.cpp
        src/VertexArray.h
        src/VertexBufferLayout.h
        src/Shader.h
        src/Shader.cpp
        src/vendor/stb_image/stb_image.h
        src/vendor/stb_image/stb_image.cpp
        src/Texture.cpp
        src/Texture.h
        src/vendor/imgui/imconfig.h
        src/vendor/imgui/imgui.cpp
        src/vendor/imgui/imgui.h
        src/vendor/imgui/imgui_demo.cpp
        src/vendor/imgui/imgui_draw.cpp
        src/vendor/imgui/imgui_impl_glfw.cpp
        src/vendor/imgui/imgui_impl_glfw.h
        src/vendor/imgui/imgui_internal.h
        src/vendor/imgui/imgui_tables.cpp
        src/vendor/imgui/imgui_widgets.cpp
        src/vendor/imgui/imstb_rectpack.h
        src/vendor/imgui/imstb_textedit.h
        src/vendor/imgui/imstb_truetype.h
        src/vendor/imgui/imgui_impl_opengl3.cpp
        src/vendor/imgui/imgui_impl_opengl3.h)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/res
        ${PROJECT_BINARY_DIR}/res
        COMMENT "Copyng resources into binary directory")

add_dependencies(VigilGameCpp copy_resources)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()
if (LINUX)
    target_link_libraries(VigilGameCpp GL GLU glut GLEW glfw X11 Xxf86vm Xrandr pthread Xi dl)
endif (LINUX)
if (APPLE)
    target_link_libraries(VigilGameCpp glfw GLEW "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif (APPLE)

add_definitions(-DGLEW_STATIC)