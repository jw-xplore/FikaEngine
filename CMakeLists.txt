cmake_minimum_required(VERSION 3.31)
project(FikaEngine)

set(CMAKE_CXX_STANDARD 20)

# Dependencies
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# imGui
ADD_LIBRARY(imgui STATIC 
			external/imgui/imgui.cpp
            external/imgui/imgui_demo.cpp
            external/imgui/imgui_draw.cpp
            external/imgui/imgui_tables.cpp
            external/imgui/imgui_widgets.cpp
            # add imgui backends you use:
            external/imgui/imgui_impl_glfw.h
			external/imgui/imgui_impl_glfw.cpp
			external/imgui/imgui_impl_opengl3.h
			external/imgui/imgui_impl_opengl3.cpp
			external/imgui/imgui_impl_opengl3_loader.h
			)
			
target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/external/backends
)

target_link_libraries(imgui
    PUBLIC
        glfw
        glad
)

# Platform-specific: link OpenGL system library (GL on Linux, OpenGL on macOS/Windows)
find_package(OpenGL REQUIRED)
target_link_libraries(imgui PUBLIC OpenGL::GL)

# Engine
add_subdirectory(engine)

# Projects
file(GLOB PROJECT_DIRS RELATIVE ${CMAKE_SOURCE_DIR} projects/*)

foreach(PROJ ${PROJECT_DIRS})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${PROJ} AND
       EXISTS ${CMAKE_SOURCE_DIR}/${PROJ}/CMakeLists.txt)
        
        message(STATUS "Adding project: ${PROJ}")
        add_subdirectory(${PROJ})
        
    endif()
endforeach()