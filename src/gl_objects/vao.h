#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>

#include "buffers/vbo.h"

using namespace std;

class VAO {
public:
    VAO(vector<shared_ptr<VBO>> &vbos, int length);
    
    ~VAO();

    virtual GLuint createVAO(vector<shared_ptr<VBO>> &vbos);

    virtual GLuint getVAO();

    virtual int getLength();

    virtual vector<shared_ptr<VBO>>& getVBOs();

    virtual void draw();

    virtual void destroy();
protected:
    GLuint vao;//vao
    vector<shared_ptr<VBO>> vbos;//массив vbo
    int length;//кол-во вершин

    VAO();

    virtual void configureVAO(vector<shared_ptr<VBO>> &vbos);
};