#include "Vec3Uniform.h"

Vec3Uniform::Vec3Uniform(const std::string &path) : Uniform(path) {

}

Vec3Uniform::Vec3Uniform(glm::vec3 value) : Uniform(value) {

}

void Vec3Uniform::uniform() const {
    glUniform3f(this->loc, this->value.x, this->value.y, this->value.z);
}