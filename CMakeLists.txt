CMAKE_MINIMUM_REQUIRED(VERSION 3.31)
PROJECT(FikaEngine)

set(CMAKE_CXX_STANDARD 20)

# External dependencies
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

# ---------------- GLAD ----------------
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(FikaEngine ${ENGINE_SOURCES})

target_link_libraries(FikaEngine
	PRIVATE
	glfw
	opengl32
	glm
	glad
)