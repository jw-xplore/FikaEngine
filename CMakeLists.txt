CMAKE_MINIMUM_REQUIRED(VERSION 3.31)
set(TARGET_NAME FikaEngine)
set(APP_NAME FikaApp)

# ---------------- Dependencies ----------------
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# ---------------- Sources ----------------
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)

list(FILTER ENGINE_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

# Engine library
add_library(${TARGET_NAME} ${ENGINE_SOURCES})

# Executable (entry point only)
add_executable(${APP_NAME} src/main.cpp)

# Link everything
target_link_libraries(${TARGET_NAME}
    PUBLIC
    glfw
    glm::glm
    glad
    opengl32
)

target_link_libraries(${APP_NAME}
    PRIVATE
    ${TARGET_NAME}
)

# Copy assets
add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:${APP_NAME}>/assets
)

# Working directory
set_target_properties(${APP_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${APP_NAME}>
)

# Filters
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source" FILES ${ENGINE_SOURCES})