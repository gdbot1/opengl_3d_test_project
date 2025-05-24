#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader/shader.h"
#include "shader/program.h"

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

    glfwTerminate();

    cout << "Hello world" << endl;
    return 0;
}