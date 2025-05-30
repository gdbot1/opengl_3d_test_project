#include "Object.h"

Object::Object(shared_ptr<VAO> vao, shared_ptr<mtrx::TransformMatrix> module_matrix) {
    this->vao = vao;
    this->module_matrix = module_matrix;
}

Object::Object(shared_ptr<VAO> vao) {
    this->vao = vao;
    this->module_matrix = make_shared<mtrx::TransformMatrix>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 1, false);
}

Object::~Object() {
    
}

void Object::setVAO(shared_ptr<VAO> vao) {
    this->vao = vao;
}

shared_ptr<VAO> Object::getVAO() {
    return this->vao;
}

shared_ptr<mtrx::TransformMatrix> Object::getModule() {
    return this->module_matrix;
}

void Object::render(RenderParam &param) {
    mtrx::uniform(param.program->getProgram(), "module_matrix", this->module_matrix->getMatrix());

    this->vao->draw();
}