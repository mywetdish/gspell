cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

set(PROJECT_NAME gspells)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp
	src/renderer/shader_program.cpp
	src/renderer/shader_program.h
	src/renderer/texture2d.cpp
	src/renderer/texture2d.h
	src/renderer/sprite.cpp
	src/renderer/sprite.h
	src/renderer/animated_sprite.cpp
	src/renderer/animated_sprite.h
	src/resources/resource_manager.cpp
	src/resources/resource_manager.h
	src/resources/stb_image.h
	src/game/game.cpp
	src/game/game.h
    src/game/character.cpp
    src/game/character.h
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

include_directories(external/glm)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res) 
