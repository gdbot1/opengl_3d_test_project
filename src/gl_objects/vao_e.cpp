#include "Vao_e.h"

using namespace std;

VAO_E::VAO_E(vector<shared_ptr<VBO>> &vbos, shared_ptr<EBO> &ebo, int length) {
    this->length = length;
    this->vbos = vbos;
    this->ebo = ebo;
    this->vao = createVAO(vbos, *ebo);
}

VAO_E::~VAO_E() {
    VAO::destroy();
}

GLuint VAO_E::createVAO(vector<shared_ptr<VBO>> &vbos, EBO &ebo) {
    GLuint vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    configureVAO(vbos);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.getEBO());

    glBindVertexArray(0);

    return vao;
}

const shared_ptr<EBO> VAO_E::getEBO() {
    return this->ebo;
}

void VAO_E::draw() {
    glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, this->length, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

VAO::VAO() {}