#include "Shader.h"

using namespace std;

Shader::Shader(const char* path, GLenum type) {
    this->shader = createShader(path, type);
    this->type = type;
}

Shader::~Shader() {
    destroy();
}

GLuint Shader::createShader(const char* path, GLuint type) {
    GLuint shader = glCreateShader(type);

    char* shaderData = readShaderData(path);

    cout << "shader data: " << shaderData << endl;

    if (shaderData == nullptr) {
	cerr << "FATAL ERROR: (shader type:" << type << ") read shader file error:" << endl;
	throw runtime_error("FATAL ERROR: read shader file error");
    }

    glShaderSource(shader, 1, &shaderData, nullptr);
    glCompileShader(shader);

    char log[512];
    if (fillShaderLog(shader, log, sizeof(log))) {
	cerr << "FATAL ERROR: (shader type:" << type << ") compile shader error: " << log << endl;
	throw runtime_error("FATAL ERROR: compile shader error");
    }

    delete[] shaderData;

    return shader;	
}

GLuint Shader::getShader() {
    return this->shader;
}

GLenum Shader::getType() {
    return this->type;
}
 
void Shader::destroy() {
    glDeleteShader(shader);
}

bool Shader::fillShaderLog(GLuint shader, char* log, int size) {
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {// == 0
	glGetShaderInfoLog(shader, size, nullptr, log);
	return true;
    }

    return false;
}

char* Shader::readShaderData(const char* path) {
    ifstream file(path, ios::binary | ios::ate);
    
    if (!file.is_open()) {
	cerr << "ERROR: file " << path << " can't be opened" << endl;
	return nullptr;
    }

    streamsize file_size = file.tellg();
    file.seekg(0, ios::beg);

    char* buffer = new char[file_size + 1];

    if (!file.read(buffer, file_size)) {
	cerr << "ERROR: read error" << endl;
	delete[] buffer;
	return nullptr;
    }

    buffer[file_size] = '\0';

    return buffer;
}