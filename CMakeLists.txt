cmake_minimum_required(VERSION 3.31.7 FATAL_ERROR)

set(project_name "3d_opengl_cpp_test")

project(${project_name})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${project_name}
	src/Main.cpp

	src/shader/Shader.cpp
	src/shader/Program.cpp

	src/graphics/utils/GLUtils.cpp

	src/graphics/gl_objects/Vao.cpp
	src/graphics/gl_objects/Vao_e.cpp

	src/graphics/gl_objects/buffers/Vbo.cpp
	src/graphics/gl_objects/buffers/Ebo.cpp
	src/graphics/gl_objects/buffers/fbo/Fbo.cpp
	src/graphics/gl_objects/buffers/fbo/LayerFbo.cpp
	src/graphics/gl_objects/buffers/fbo/utils/FBOUtils.cpp

	src/graphics/gl_objects/texture/Texture.cpp
	src/graphics/gl_objects/texture/DepthTexture.cpp
	src/graphics/gl_objects/texture/utils/TextureUtils.cpp

	src/graphics/elements/window/Window.cpp

	src/graphics/elements/window/callback/GLFWCallback.cpp
	src/graphics/elements/window/callback/keyCallback/KeyEvent.cpp
	src/graphics/elements/window/callback/keyCallback/KeyDispatcher.cpp
	src/graphics/elements/window/callback/mouseCallback/events/MouseButtonEvent.cpp
	src/graphics/elements/window/callback/mouseCallback/MouseDispatcher.cpp
	src/graphics/elements/window/callback/windowCallback/events/FramebufferSizeEvent.cpp
	src/graphics/elements/window/callback/windowCallback/WindowDispatcher.cpp

	src/graphics/param/RenderParam.cpp

 	src/matrix/utils/MatrixUtils.cpp

	src/matrix/projection/ProjectionMatrix.cpp
	src/matrix/projection/perspective/PerspectiveMatrix.cpp
	src/matrix/projection/perspective/PerspectiveWindowMatrix.cpp
	src/matrix/projection/OrthogonalMatrix.cpp

	src/matrix/transform/position/Position.cpp
	src/matrix/transform/rotation/Rotation.cpp
	src/matrix/transform/scale/Scale.cpp

	src/matrix/transform/TransformMatrix.cpp
	src/matrix/transform/transforms/ViewMatrix.cpp
	src/matrix/transform/transforms/ModelMatrix.cpp

	src/world/camera/Camera.cpp

	src/events/update/UpdateDispatcher.cpp
	src/events/update/context/UpdateContext.cpp
	src/events/update/listeners/Updatable.cpp
	src/events/update/listeners/DynamicUpdatable.cpp

	src/utils/file/files/File.cpp
	src/utils/file/files/folders/Folder.cpp
	src/utils/file/utils/FileUtils.cpp

	src/utils/time/Timer.cpp

	src/utils/collision/simplex/Simplex.cpp
	src/utils/collision/simplex/utils/SimplexUtils.cpp
	src/utils/collision/gjk/GJKUtils.cpp
	src/utils/collision/gjk/hitbox/obb/OBBHitbox.cpp
	src/utils/collision/epa/EPAUtils.cpp

	src/utils/math/MathUtils.cpp

	src/engine/Engine.cpp

	src/engine/controller/controllers/Controller.cpp
	src/engine/controller/controllers/TestController.cpp

	src/engine/sample/samples/TestSample.cpp

	src/engine/update/Updater.cpp

	src/world/scene/Scene.cpp
	src/world/scene/elements/BindFBO.cpp
	src/world/scene/elements/Swap.cpp
	src/world/scene/elements/Display.cpp

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

target_include_directories(${project_name} PRIVATE ${PROJECT_SOURCE_DIR}/src)