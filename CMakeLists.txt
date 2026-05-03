cmake_minimum_required(VERSION 3.31)
project(FikaEngine)

set(CMAKE_CXX_STANDARD 20)

# Dependencies
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

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