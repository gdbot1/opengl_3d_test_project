#include "program.h"

using namespace std;

Program::Program(vector<shared_ptr<Shader>> &shaders) {
    this->program = createProgram(shaders);
}

Program::~Program() {
    destroy();
}

GLuint Program::getProgram() {
    return this->program;
}

void Program::destroy() {
    glDeleteProgram(program);
}

GLuint Program::createProgram(const vector<shared_ptr<Shader>> &shaders) {
    GLuint program = glCreateProgram();

    for (int i = 0; i < shaders.size(); i++) {
	glAttachShader(program, shaders[i]->getShader());
    }

    glLinkProgram(program);

    char log[512];
    if (fillProgramLog(program, log, sizeof(log))) {
	cerr << "FATAL ERROR: Program link error. Log: " << log << endl;
	throw runtime_error("FATAL ERROR: Program link error");
    }

    return program;
}

bool Program::fillProgramLog(GLuint program, char* log, int size) {
    GLint success;

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {// == 0
	glGetProgramInfoLog(program, size, nullptr, log);
	return true;
    }

    return false;
}