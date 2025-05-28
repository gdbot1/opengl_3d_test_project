#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>

#include "Vao.h"
#include "buffers/Vbo.h"
#include "buffers/Ebo.h"

using namespace std;

class VAO_E : public VAO {
public:
    VAO_E(vector<shared_ptr<VBO>> &vbos, shared_ptr<EBO>& ebo, int length);
    
    ~VAO_E();

    GLuint createVAO(vector<shared_ptr<VBO>> &vbos, EBO &ebo);

    const shared_ptr<EBO> getEBO();

    void draw() override;
protected:
    shared_ptr<EBO> ebo;
};