#include "TextureUniform.h"

TextureUniform::TextureUniform(const std::string &path) : Uniform(path) {

}

void TextureUniform::uniform() const {
    value.first->bindSampler(value.second);

    glUniform1i(this->loc, value.second);
}