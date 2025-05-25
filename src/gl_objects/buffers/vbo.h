#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>

using namespace std;

class VBO {
public:
    VBO(float* vertices, int arr_length, int size);

    VBO(vector<float> &vertices, int size);

    ~VBO();

    GLuint createVBO(float* arr, int length);

    GLuint getVBO();

    int getSize();

    int getLength();

    void destroy();
private:
    GLuint vbo;
    int size, length;//size - кол-во float на 1 вершину, length - кол-во вершин в VBO
};