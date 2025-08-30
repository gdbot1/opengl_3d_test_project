#pragma once

#include <string>
#include <utility>
#include <memory>

#include <glm/glm.hpp>

#include "graphics/gl_objects/uniform/Uniform.h"
#include "graphics/gl_objects/texture/Texture.h"

class TextureUniform : public Uniform<std::pair<std::shared_ptr<tex::Texture>, int>> {
public:
    TextureUniform(const std::string &path);

    virtual ~TextureUniform() = default;

    virtual void uniform() const override;
};