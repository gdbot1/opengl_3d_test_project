#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader/Shader.h"
#include "shader/Program.h"

#include "gl_objects/Vao_e.h"
#include "gl_objects/Vao.h"

#include "gl_objects/buffers/Vbo.h"
#include "gl_objects/buffers/Ebo.h"

#include "world/camera/Camera.h"

using namespace std;

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

    auto vert_shader = make_shared<Shader>("../shaders/test.vert", GL_VERTEX_SHADER);
    auto frag_shader = make_shared<Shader>("../shaders/test.frag", GL_FRAGMENT_SHADER);

    vector<shared_ptr<Shader>> shaders = {vert_shader, frag_shader};

    Program program(shaders);

    cout << "PROGRAM: " << program.getProgram() << endl;

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

    glUseProgram(program.getProgram());

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
    
    auto vert_vbo = make_shared<VBO>(vert, 3);
    auto col_vbo = make_shared<VBO>(col, 3);

    vector<shared_ptr<VBO>> vbos = {vert_vbo, col_vbo};

    vector<int> ids = {
	0, 1, 2,
	0, 2, 3 
    };

    EBO ebo(ids);

    VAO_E vao(vbos, ebo, ebo.getLength());

    glm::vec3 pos(0, 0, 3), rot(0, 0, 0), scal(1, 1, 1);

    Camera camera(pos, rot, scal);

    camera.setPerspectiveProjectionMatrix(90, 1, 0.1f, 100);

    int view_matrix_uniform = glGetUniformLocation(program.getProgram(), "view_matrix"), projection_matrix_uniform = glGetUniformLocation(program.getProgram(), "projection_matrix");

    float theta = 0;

    while(!glfwWindowShouldClose(window)) {
	theta ++;

	glClear(GL_COLOR_BUFFER_BIT);
	
	camera.setRotation(glm::vec3(0, theta, 0));
	
	glm::mat4 view_matrix = camera.getViewMatrix();
	glUniformMatrix4fv(view_matrix_uniform, 1, GL_FALSE, glm::value_ptr(view_matrix));
	
	glm::mat4 projection_matrix = camera.getProjectionMatrix();

	glUniformMatrix4fv(projection_matrix_uniform, 1, GL_FALSE, glm::value_ptr(projection_matrix));
	
	vao.draw();

	glfwPollEvents();
	glfwSwapBuffers(window);
    }

    glfwTerminate();

    cout << "Hello world" << endl;
    return 0;
}