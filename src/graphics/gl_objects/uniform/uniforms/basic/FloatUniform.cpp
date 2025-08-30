#include "FloatUniform.h"

FloatUniform::FloatUniform(const std::string &path) : Uniform(path) {

}

FloatUniform::FloatUniform(float value) : Uniform(value) {

}

void FloatUniform::uniform() const {
    glUniform1f(this->loc, this->value);
}