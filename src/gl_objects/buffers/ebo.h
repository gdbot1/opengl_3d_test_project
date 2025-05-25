#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>

using namespace std;

class EBO {
public:
    EBO(int* vertices, int length);

    EBO(vector<int> &vertices);

    ~EBO();

    GLuint createEBO(int* arr, int length);

    GLuint getEBO();

    int getLength();

    void destroy();
private:
    GLuint ebo;
    int length;//length - кол-во вершин в EBO
};