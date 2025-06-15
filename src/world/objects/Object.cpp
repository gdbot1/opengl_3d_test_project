#include "Object.h"

#include <iostream>

Object::Object(shared_ptr<VAO> vao, shared_ptr<mtrx::TransformMatrix> model_matrix, shared_ptr<tex::Texture> texture) {
    this->vao = vao;
    this->model_matrix = model_matrix;
    this->texture = texture;
}

Object::Object(shared_ptr<VAO> vao, shared_ptr<mtrx::TransformMatrix> model_matrix) {
    this->vao = vao;
    this->model_matrix = model_matrix;
    this->texture = nullptr;
}

Object::Object(shared_ptr<VAO> vao, shared_ptr<tex::Texture> texture) {
    this->vao = vao;
    this->texture = texture;
    this->model_matrix = make_shared<mtrx::ModelMatrix>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 1);
}


Object::Object(shared_ptr<VAO> vao) {
    this->vao = vao;
    this->model_matrix = make_shared<mtrx::ModelMatrix>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 1);
}

Object::~Object() {
    
}

void Object::setVAO(shared_ptr<VAO> vao) {
    this->vao = vao;
}

void Object::setModel(shared_ptr<mtrx::TransformMatrix> model_matrix) {
    this->model_matrix = model_matrix;
}

void Object::setTexture(shared_ptr<tex::Texture> texture) {
    this->texture = texture;
}

shared_ptr<VAO> Object::getVAO() {
    return this->vao;
}

shared_ptr<mtrx::TransformMatrix> Object::getModel() {
    return this->model_matrix;
}

shared_ptr<tex::Texture> Object::getTexture() {
    return this->texture;
}

void Object::render(RenderParam &param) {
    if (texture) {
	texture->bindSampler(0);
	tex::uniformInteger(param.program->getProgram(), "texStatus", 1);
	tex::uniformInteger(param.program->getProgram(), "tex", 0);
    }
    else {
	tex::uniformInteger(param.program->getProgram(), "texStatus", 0);
    }

    mtrx::uniform(param.program->getProgram(), "model_matrix", this->model_matrix->getMatrix());

    this->vao->render(param);
}