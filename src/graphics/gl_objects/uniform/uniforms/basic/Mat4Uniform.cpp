#include "Mat4Uniform.h"

Mat4Uniform::Mat4Uniform(const std::string &path) : Uniform(path) {

}

void Mat4Uniform::uniform() const {
    glUniformMatrix4fv(this->loc, 1, GL_FALSE, glm::value_ptr(value));
}