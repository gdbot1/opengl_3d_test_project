cmake_minimum_required(VERSION 3.31.7 FATAL_ERROR)

set(project_name "3d_opengl_cpp_test")

project(${project_name})

add_executable(${project_name}
	src/Main.cpp

	src/shader/Shader.cpp
	src/shader/Program.cpp

	src/gl_objects/Vao.cpp
	src/gl_objects/Vao_e.cpp

	src/gl_objects/buffers/Vbo.cpp
	src/gl_objects/buffers/Ebo.cpp

	src/world/camera/Camera.cpp

	src/world/objects/Object.cpp
	src/world/objects/Cube.cpp
)

add_subdirectory(libs/glfw)
add_subdirectory(libs/glad)
add_subdirectory(libs/glm-master)
add_subdirectory(libs/libigl-stb-master)

target_link_libraries(${project_name} glfw)
target_link_libraries(${project_name} glad)
target_link_libraries(${project_name} glm)
target_link_libraries(${project_name} igl_stb_image)