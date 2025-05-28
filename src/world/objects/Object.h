#pragma once

#include "../../gl_objects/Vao.h"
#include "../../graphics/IRenderable.h"

class Object : public IRenderable {
public:
    Object(shared_ptr<VAO> vao);

    ~Object();

    virtual void setVAO(shared_ptr<VAO> vao);

    virtual shared_ptr<VAO> getVAO();

    virtual void render() override;
protected:
    shared_ptr<VAO> vao;

    Object() = default;//пустой конструктор
};