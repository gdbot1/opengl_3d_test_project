#pragma once

#include "../../gl_objects/Vao.h"

#include "../../graphics/IRenderable.h"

#include "../../matrix/utils/MatrixUtils.h"

#include "../../matrix/transform/TransformMatrix.h"

class Object : public IRenderable {
public:
    Object(shared_ptr<VAO> vao, shared_ptr<mtrx::TransformMatrix> module_matrix);

    Object(shared_ptr<VAO> vao);

    ~Object();

    virtual void setVAO(shared_ptr<VAO> vao);

    virtual shared_ptr<VAO> getVAO();

    virtual shared_ptr<mtrx::TransformMatrix> getModule();

    virtual void render(RenderParam &param) override;
protected:
    shared_ptr<mtrx::TransformMatrix> module_matrix;
    shared_ptr<VAO> vao;

    Object() = default;//пустой конструктор
};