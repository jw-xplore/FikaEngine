set(ENGINE_NAME FikaEngine)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

add_library(${ENGINE_NAME} ${ENGINE_SOURCES})

target_link_libraries(${ENGINE_NAME}
    PUBLIC
    glfw
    glm::glm
    glad
    opengl32
)

target_include_directories(${ENGINE_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Filters (optional)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source" FILES ${ENGINE_SOURCES})