#pragma once

#include "../../gl_objects/Vao.h"

#include "../../gl_objects/texture/Texture.h"

#include "../../gl_objects/texture/utils/TextureUtils.h"

#include "../../graphics/IRenderable.h"

#include "../../matrix/utils/MatrixUtils.h"

#include "../../matrix/transform/TransformMatrix.h"

class Object : public IRenderable {
public:
    Object(shared_ptr<VAO> vao, shared_ptr<mtrx::TransformMatrix> model_matrix, shared_ptr<tex::Texture> texture);

    Object(shared_ptr<VAO> vao, shared_ptr<mtrx::TransformMatrix> model_matrix);

    Object(shared_ptr<VAO> vao, shared_ptr<tex::Texture> texture);

    Object(shared_ptr<VAO> vao);

    ~Object();

    virtual void setVAO(shared_ptr<VAO> vao);

    virtual void setModel(shared_ptr<mtrx::TransformMatrix> model_matrix);

    virtual void setTexture(shared_ptr<tex::Texture> texture);

    virtual shared_ptr<VAO> getVAO();

    virtual shared_ptr<mtrx::TransformMatrix> getModel();

    virtual shared_ptr<tex::Texture> getTexture();

    virtual void render(RenderParam &param) override;
protected:
    shared_ptr<tex::Texture> texture;
    shared_ptr<mtrx::TransformMatrix> model_matrix;
    shared_ptr<VAO> vao;

    Object() = default;//пустой конструктор
};