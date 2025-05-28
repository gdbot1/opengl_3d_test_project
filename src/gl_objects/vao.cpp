#include "Vao.h"

using namespace std;

VAO::VAO(vector<shared_ptr<VBO>> &vbos, int length) {
    this->vbos = vbos;
    this->length = length;
    this->vao = createVAO(vbos);
}

VAO::~VAO() {
    destroy();
}

GLuint VAO::createVAO(vector<shared_ptr<VBO>> &vbos) {
    GLuint vao;

    glGenVertexArrays(1, &vao); 
    glBindVertexArray(vao);
    
    configureVAO(vbos);

    glBindVertexArray(0);

    return vao;
}

GLuint VAO::getVAO() {
    return this->vao;
}

int VAO::getLength() {
    return this->length;
}

vector<shared_ptr<VBO>>& VAO::getVBOs() {
    return this->vbos;
}

void VAO::draw() {
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, length);

    glBindVertexArray(0);
}

void VAO::destroy() {
    glDeleteVertexArrays(1, &this->vao);
}

void VAO::configureVAO(vector<shared_ptr<VBO>> &vbos) {
    for (int i = 0; i < vbos.size(); i++) {
	glBindBuffer(GL_ARRAY_BUFFER, vbos[i]->getVBO());
	glVertexAttribPointer(i, vbos[i]->getSize(), GL_FLOAT, GL_FALSE, vbos[i]->getSize() * sizeof(float), nullptr);
	glEnableVertexAttribArray(i);
    }
}