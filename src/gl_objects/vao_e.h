#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>

#include "vao.h"
#include "buffers/vbo.h"
#include "buffers/ebo.h"

using namespace std;

class VAO_E : public VAO {
public:
    VAO_E(vector<shared_ptr<VBO>> &vbos, EBO& ebo, int length);
    
    ~VAO_E();

    GLuint createVAO(vector<shared_ptr<VBO>> &vbos, EBO &ebo);

    const EBO* getEBO();

    void draw();
protected:
    EBO* ebo;
};