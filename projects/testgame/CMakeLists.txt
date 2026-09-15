set(APP_NAME testgame)
set(APP_SOURCE_DIR ${CMAKE_SOURCE_DIR}/projects/${APP_NAME})
set(APP_BINARY_DIR ${CMAKE_BINARY_DIR}/projects/${APP_NAME})

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

add_executable(${APP_NAME} ${APP_SOURCES})

target_link_libraries(${APP_NAME}
    PRIVATE
    FikaEngine
)

# Copy engine shared assets
add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:${APP_NAME}>/assets/common
)

# Copy project assets
add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${APP_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:${APP_NAME}>/assets
)

# Setup metadata
configure_file(
    "${CMAKE_SOURCE_DIR}/engine/templates/projbuildmeta.json.in"
    "${CMAKE_BINARY_DIR}/projects/${APP_NAME}/meta.json"
    @ONLY
)

set_target_properties(${APP_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${APP_NAME}>
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source" FILES ${APP_SOURCES})