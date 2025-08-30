#include "Vec2Uniform.h"

Vec2Uniform::Vec2Uniform(const std::string &path) : Uniform(path) {

}

void Vec2Uniform::uniform() const {
    glUniform2f(this->loc, this->value.x, this->value.y);
}