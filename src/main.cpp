#include <iostream>
#include <vector>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader/Shader.h"
#include "shader/Program.h"

#include "gl_objects/Vao_e.h"
#include "gl_objects/Vao.h"

#include "gl_objects/buffers/Vbo.h"
#include "gl_objects/buffers/Ebo.h"

#include "gl_objects/texture/Texture.h"

#include "matrix/utils/MatrixUtils.h"

#include "matrix/projection/ProjectionMatrix.h"

#include "matrix/projection/OrthogonalMatrix.h"
#include "matrix/projection/PerspectiveMatrix.h"

#include "matrix/transform/TransformMatrix.h"

#include "world/camera/Camera.h"

#include "graphics/param/RenderParam.h"

#include "world/objects/Object.h"
#include "world/objects/Cube.h"

using namespace std;

void keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        cout << "key pressed" << endl;

	if (key == GLFW_KEY_A) {
	    cout << "pressed A" << endl;
	}
    }
    else if (action == GLFW_RELEASE) {
	cout << "key released" << endl;
    }
}

void windowResize(GLFWwindow* window, int width, int height) {
    cout << "window resized, w:" << width << " h:" << height << endl;
    glViewport(0, 0, width, height);
}

int main() {
    if (!glfwInit()) {
	cerr << "FATAL ERROR: glfw can't be inited" << endl;
	return -1;
    }

    glfwDefaultWindowHints();

    GLFWwindow* window = glfwCreateWindow(500, 500, "3D OpenGL", nullptr, nullptr);

    if (window == nullptr) {
	cerr << "FATAL ERROR: window can't be created" << endl;
	glfwTerminate();
	return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGL()) {
	cerr << "FATAL ERROR: glad can't be inited" << endl;
	glfwTerminate();
	return -1;
    }

    //Enable
    glEnable(GL_DEPTH_TEST);

    auto vert_shader = make_shared<Shader>("../shaders/test.vert", GL_VERTEX_SHADER);
    auto frag_shader = make_shared<Shader>("../shaders/test.frag", GL_FRAGMENT_SHADER);

    vector<shared_ptr<Shader>> shaders = {vert_shader, frag_shader};

    shared_ptr<Program> program = make_shared<Program>(shaders);

    cout << "PROGRAM: " << program->getProgram() << endl;
	
    //render param
    RenderParam param(program);

    shared_ptr<tex::Texture> texture = make_shared<tex::Texture>("../textures/03.png");

    cout << "texture loaded: w: " << texture->getWidth() << " h: " << texture->getHeight() << " t: " << texture->getTexture() << endl;

    glfwSetKeyCallback(window, keyPressed);
    glfwSetFramebufferSizeCallback(window, windowResize);

/*
    vector<float> vertices = {
	1, 0, 2,
	3, 2, 1,
	2, 4, 4,
	8, -1, 1
    };

    VBO vbo(vertices, 3);

    vector<int> ind = {
	1, 2, 3,
	1, 3, 4,
	2, 4, 1,
	3, 1, 2
    };

    EBO ebo(ind);
*/

    glUseProgram(program->getProgram());

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
	0, 1,
	0, 0,
	1, 0,
	1, 1
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

    Cube cube(-0.5f, -0.5f, -0.5f, 1, 1, 1);
    cube.getModel()->setPosition(glm::vec3(2, 0, 2));//change cube position
    //cube.setTexture(texture);

    glm::vec3 pos(0, 0, 1), rot(0, 0, 0), scal(1, 1, 1);

    Camera camera(pos, rot, scal, 90, 1, 0.1f, 100);

    int view_matrix_uniform = glGetUniformLocation(program->getProgram(), "view_matrix"), projection_matrix_uniform = glGetUniformLocation(program->getProgram(), "projection_matrix");

    float theta = 0;

    while(!glfwWindowShouldClose(window)) {
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

	object.render(param);

	cube.render(param);

	glfwPollEvents();
	glfwSwapBuffers(window);
    }

    glfwTerminate();

    cout << "Hello world" << endl;
    return 0;
}