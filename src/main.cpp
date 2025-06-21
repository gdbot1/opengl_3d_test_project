#include <iostream>
#include <vector>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader/Shader.h"
#include "shader/Program.h"

#include "graphics/gl_objects/Vao_e.h"
#include "graphics/gl_objects/Vao.h"

#include "graphics/gl_objects/buffers/Vbo.h"
#include "graphics/gl_objects/buffers/Ebo.h"
#include "graphics/gl_objects/buffers/fbo/Fbo.h"
#include "graphics/gl_objects/buffers/fbo/LayerFbo.h"

#include "graphics/gl_objects/texture/Texture.h"
#include "graphics/gl_objects/texture/DepthTexture.h"

#include "graphics/elements/window/Window.h"

#include "graphics/param/RenderParam.h"

#include "matrix/utils/MatrixUtils.h"

#include "matrix/projection/ProjectionMatrix.h"

#include "matrix/projection/OrthogonalMatrix.h"
#include "matrix/projection/perspective/PerspectiveMatrix.h"
#include "matrix/projection/perspective/PerspectiveWindowMatrix.h"

#include "matrix/transform/TransformMatrix.h"

#include "world/camera/Camera.h"

#include "world/objects/Object.h"
#include "world/objects/Cube.h"

#include "events/Dispatcher.h"

#include "graphics/elements/window/callback/GLFWCallback.h"
#include "graphics/elements/window/callback/keyCallback/KeyDispatcher.h"
#include "graphics/elements/window/callback/mouseCallback/MouseDispatcher.h"
#include "graphics/elements/window/callback/windowCallback/WindowDispatcher.h"

using namespace std;

class O : public callback::WindowListener {
public:
    O(shared_ptr<tex::Texture> texture) {
	this->texture = texture;
    }

    void draw() {
	texture->bind();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(-aspect, -1);
	glTexCoord2f(1, 0); glVertex2f( aspect, -1);
	glTexCoord2f(1, 1); glVertex2f( aspect,  1);
	glTexCoord2f(0, 1); glVertex2f(-aspect,  1);
	glEnd();

	texture->unbind();
    }

    void onFramebufferSizeEvent(callback::FramebufferSizeEvent &event) {
	aspect = static_cast<float>(event.getWidth()) / static_cast<float>(event.getHeight());
    }
private:
    shared_ptr<tex::Texture> texture;
    float aspect = 1;
};

class L : public callback::KeyListener, public callback::MouseListener, public callback::WindowListener {
public:
    void onKeyEvent(callback::KeyEvent &event) override {
	cout << "KeyEvent: " << event.getKey() << " " << event.getAction() << endl;
    }

    void onMouseButtonEvent(callback::MouseButtonEvent &event) override {
	cout << "MouseEvent: " << event.getButton() << " " << event.getAction() << endl;
    }

    void onFramebufferSizeEvent(callback::FramebufferSizeEvent &event) {
	cout << "WindowEvent: " << event.getWidth() << " " << event.getHeight() << endl;
	glViewport(0, 0, event.getWidth(), event.getHeight());
    }
};

int main() {
    if (!glfwInit()) {
	cerr << "FATAL ERROR: glfw can't be inited" << endl;
	return -1;
    }
    
    gr::Window window(500, 500, "OpenGL Project");

    L l;

    window.createCallback();

    window.getCallback()->getKeyEvent()->addListener(&l);
    window.getCallback()->getMouseEvent()->addListener(&l);
    window.getCallback()->getWindowEvent()->addListener(&l);

    if (!gladLoadGL()) {
	cerr << "FATAL ERROR: glad can't be inited" << endl;
	glfwTerminate();
	return -1;
    }

    //Enable
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    auto vert_shader = make_shared<Shader>("../shaders/test.vert", GL_VERTEX_SHADER);
    auto frag_shader = make_shared<Shader>("../shaders/test.frag", GL_FRAGMENT_SHADER);

    vector<shared_ptr<Shader>> shaders = {vert_shader, frag_shader};

    shared_ptr<Program> program = make_shared<Program>(shaders);

    cout << "PROGRAM: " << program->getProgram() << endl;
	
    //render param
    RenderParam param(program);

    shared_ptr<tex::Texture> texture = make_shared<tex::Texture>("../textures/03.png");
    
    LayerFBO fbo(2048, 2048);

/*
    shared_ptr<tex::Texture> normal_texture = make_shared<tex::Texture>(texture->getWidth(), texture->getHeight());
    shared_ptr<tex::DepthTexture> depth_texture = make_shared<tex::DepthTexture>(texture->getWidth(), texture->getHeight());

    FBO fbo;

    fbo.bind();
    fbo.linkTexture((*normal_texture), GL_COLOR_ATTACHMENT0, 0);
    fbo.linkTexture((*depth_texture), GL_DEPTH_ATTACHMENT, 0);
    fbo.unbind();
*/

    cout << "texture loaded: w: " << texture->getWidth() << " h: " << texture->getHeight() << " t: " << endl;

    //glUseProgram(program->getProgram());

    vector<float> vert = {
	-0.5f, -0.5f, 1,
	-0.5f, 0.5f, 1,
	0.5f, 0.5f, 1,
	0.5f, -0.5f, 1
    };

    vector<float> col = {
	1, 0, 0,
	0, 1, 0,
	0, 0, 1,
	1, 1, 0
    };

    vector<float> texCords = {
	1, 0,
	1, 1,
	0, 1,
	0, 0
    };
    
    auto vert_vbo = make_shared<VBO>(vert, 3);
    auto col_vbo = make_shared<VBO>(col, 3);
    auto tex_vbo = make_shared<VBO>(texCords, 2);

    vector<shared_ptr<VBO>> vbos = {vert_vbo, col_vbo, tex_vbo};

    vector<int> ids = {
	0, 1, 2,
	0, 2, 3 
    };

    shared_ptr<EBO> ebo = make_shared<EBO>(ids);

    shared_ptr<VAO_E> vao = make_shared<VAO_E>(vbos, ebo, ebo->getLength());

    Object object(vao, texture);

    Object object2(vao, fbo.getColorTexture());
    object2.getModel()->setPosition(glm::vec3(1, 1, 0.5f));
    object2.getModel()->setRotation(glm::vec3(-25, 45, 0));

    Cube cube(-0.5f, -0.5f, -0.5f, 1, 1, 1);
    cube.getModel()->setPosition(glm::vec3(2, 0, 2));//change cube position
    //cube.setTexture(texture);

    glm::vec3 pos(0, 0, 1), rot(0, 0, 0), scal(1, 1, 1);

    //Camera camera(pos, rot, scal, 90, 1, 0.1f, 100);
    
    shared_ptr<mtrx::PerspectiveWindowMatrix> projection_matrix = make_shared<mtrx::PerspectiveWindowMatrix>(90, 1, 0.1f, 100);
    
    window.getCallback()->getWindowEvent()->addListener(&(*projection_matrix));

    Camera camera(pos, rot, scal, projection_matrix);

    int view_matrix_uniform = glGetUniformLocation(program->getProgram(), "view_matrix"), projection_matrix_uniform = glGetUniformLocation(program->getProgram(), "projection_matrix");

    float theta = 0;

    glClearColor(1, 1, 1, 1);

    O o(fbo.getColorTexture());

    while(!glfwWindowShouldClose(window.getWindow())) {
        glUseProgram(program->getProgram());
	theta ++;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	camera.getView()->setRotation(glm::vec3(0, cos(theta*3.14f/180) * 45 + 180, 0));

	//cube squash
	cube.getModel()->setRotation(glm::vec3(0, theta, theta/2));
	cube.getModel()->setScale(glm::vec3(1, cos(theta*3.14f/180)+2, 1));
	
	glm::mat4 view_matrix = camera.getView()->getMatrix();
	glUniformMatrix4fv(view_matrix_uniform, 1, GL_FALSE, glm::value_ptr(view_matrix));

	glm::mat4 projection_matrix = camera.getProjection()->getMatrix();

	glUniformMatrix4fv(projection_matrix_uniform, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	fbo.bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	object.render(param);
	object2.render(param);
	cube.render(param);
	fbo.unbind();

	object.render(param);

	object2.render(param);

	cube.render(param);
	
	glUseProgram(0);

	o.draw();

	glfwPollEvents();
	glfwSwapBuffers(window.getWindow());
    }

    glfwTerminate();

    cout << "Hello world" << endl;
    return 0;
}