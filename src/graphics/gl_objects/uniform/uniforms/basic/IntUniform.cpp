#include "IntUniform.h"

IntUniform::IntUniform(const std::string &path) : Uniform(path) {

}

void IntUniform::uniform() const {
    glUniform1i(this->loc, this->value);
}