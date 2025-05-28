#include "Object.h"

Object::Object(shared_ptr<VAO> vao) {
    this->vao = vao;
}

Object::~Object() {
    
}

void Object::setVAO(shared_ptr<VAO> vao) {
    this->vao = vao;
}

shared_ptr<VAO> Object::getVAO() {
    return this->vao;
}

void Object::render() {
    this->vao->draw();
}