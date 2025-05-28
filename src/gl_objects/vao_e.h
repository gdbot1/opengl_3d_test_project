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
    VAO_E(vector<shared_ptr<VBO>> &vbos, EBO& ebo, int length);
    
    ~VAO_E();

    GLuint createVAO(vector<shared_ptr<VBO>> &vbos, EBO &ebo);

    const EBO* getEBO();

    void draw() override;
protected:
    EBO* ebo;
};