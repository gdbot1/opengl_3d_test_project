#include "Vbo.h"

using namespace std;

VBO::VBO(float* vertices, int arr_length, int size) {
    this->size = size;
    this->length = arr_length / size;

    cout << "LENGTH: " << arr_length << endl; 

    this->vbo = createVBO(vertices, arr_length);
}

VBO::VBO(vector<float> &vertices, int size) {
    this->size = size;
    this->length = vertices.size() / size;

    cout << "LENGTH: " << (length * size) << endl; 

    this->vbo = createVBO(vertices.data(), vertices.size());
}

VBO::~VBO() {
    cout << "VBO: " << vbo << " - destroyed" << endl;
    destroy();
}

GLuint VBO::createVBO(float* arr, int length) {
    GLuint vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, length * sizeof(float), arr, GL_STATIC_DRAW);

    cout << "VBO: " << vbo << " - created" << endl;

    return vbo;
}

GLuint VBO::getVBO() {
    return this->vbo;
}

int VBO::getSize() {
    return this->size;
}

int VBO::getLength() {
    return this->length;
}

void VBO::destroy() {
    glDeleteBuffers(1, &vbo);
}