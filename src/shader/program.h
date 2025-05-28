#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>

#include "Shader.h"

using namespace std;

class Program {
public:
    Program(vector<shared_ptr<Shader>> &shaders);

    ~Program();

    GLuint getProgram();

    void destroy();

    GLuint createProgram(const vector<shared_ptr<Shader>> &shaders);
private:
    GLuint program;

    bool fillProgramLog(GLuint program, char* log, int size);
};