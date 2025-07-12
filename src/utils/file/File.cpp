#include "File.h"

fls::File::File(const std::string &name, fls::Type type) : name(name), type(type) {}

fls::File::~File() {}

std::string fls::File::getName() const {
    return this->name;
}

fls::Type fls::File::getType() const {
    return this->type;
}