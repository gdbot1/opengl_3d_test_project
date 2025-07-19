#include "File.h"

fls::File::File(const std::string &name, fls::Type type) : name(name), type(type) {
    this->parent = nullptr;
}

fls::File::~File() {}

std::string fls::File::getName() const {
    return this->name;
}

fls::Type fls::File::getType() const {
    return this->type;
}

void fls::File::setParent(std::shared_ptr<fls::IFile> parent) {
    std::shared_ptr<fls::IFolder> folder = std::dynamic_pointer_cast<fls::IFolder>(parent);

    if (this->parent) {
	this->parent->remove(this->getName());//удаление из предыдущего места хранения (что-бы избежать дублирования)
    }

    this->parent = folder;
}

std::shared_ptr<fls::IFile> fls::File::getParent() const {
    return this->parent;
}