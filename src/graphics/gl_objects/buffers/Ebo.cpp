#include "Ebo.h"

using namespace std;

EBO::EBO(int* vertices, int length) {
    this->length = length;
    cout << "length: " << length << endl;
    this->ebo = createEBO(vertices, length);
}

EBO::EBO(vector<int> &vertices) {
    this->length = vertices.size();
    cout << "length: " << length << endl;
    this->ebo = createEBO(vertices.data(), length);
}

EBO::~EBO() {
    cout << "EBO: " << ebo << " - destroyed" << endl;
    destroy();
}

GLuint EBO::createEBO(int* arr, int length) {
    GLuint ebo;

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * sizeof(int), arr, GL_STATIC_DRAW);

    return ebo;
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint EBO::getEBO() {
    return this->ebo;
}

int EBO::getLength() {
    return this->length;
}

void EBO::destroy() {
    glDeleteBuffers(1, &ebo);
}