#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <memory>

using namespace std;

class Shader {
public:
    Shader(const char* path, GLenum type);

    ~Shader();

    GLuint createShader(const char* path, GLuint type);

    GLuint getShader();

    GLenum getType();

    void destroy();    
private:
    GLuint shader;
    GLenum type;

    bool fillShaderLog(GLuint shader, char* log, int size);

    char* readShaderData(const char* path);
};