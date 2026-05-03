set(APP_NAME testgame)

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

add_executable(${APP_NAME} ${APP_SOURCES})

target_link_libraries(${APP_NAME}
    PRIVATE
    FikaEngine
)

# Copy assets (project-specific or shared)
add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:${APP_NAME}>/assets
)

set_target_properties(${APP_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${APP_NAME}>
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source" FILES ${APP_SOURCES})