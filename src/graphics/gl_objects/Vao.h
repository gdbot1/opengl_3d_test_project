#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>

#include "../IRenderable.h"

#include "buffers/Vbo.h"

using namespace std;

class VAO : public IRenderable {
public:
    VAO(vector<shared_ptr<VBO>> &vbos, int length);
    
    ~VAO();

    virtual GLuint createVAO(vector<shared_ptr<VBO>> &vbos);

    virtual GLuint getVAO();

    virtual int getLength();

    virtual vector<shared_ptr<VBO>>& getVBOs();

    virtual void render(RenderParam &param) override;

    virtual void destroy();
protected:
    GLuint vao;//vao
    vector<shared_ptr<VBO>> vbos;//массив vbo
    int length;//кол-во вершин

    VAO();

    virtual void configureVAO(vector<shared_ptr<VBO>> &vbos);
};