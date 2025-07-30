#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>

#include "utils/IBindable.h"

using namespace std;

class EBO : IBindable {
public:
    EBO(int* vertices, int length);

    EBO(vector<int> &vertices);

    ~EBO();

    GLuint createEBO(int* arr, int length);

    void bind() override;

    void unbind() override;

    GLuint getEBO();

    int getLength();

    void destroy();
private:
    GLuint ebo;
    int length;//length - кол-во вершин в EBO
};