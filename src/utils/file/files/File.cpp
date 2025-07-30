#include "File.h"

fls::File::File(const std::string &name, fls::Type type) : name(name), type(type) {
    this->parent.reset();
}

std::string fls::File::getName() const {
    return this->name;
}

fls::Type fls::File::getType() const {
    return this->type;
}

void fls::File::setParent(std::shared_ptr<fls::IFile> parent) {
    std::shared_ptr<fls::IFolder> folder = std::dynamic_pointer_cast<fls::IFolder>(parent);

    std::shared_ptr<fls::IFolder> folder_parent = this->parent.lock();

    if (folder_parent) {
	folder_parent->remove(this->getName());//удаление из предыдущего места хранения (что-бы избежать дублирования)
    }

    if (folder) {
	this->parent = folder;
    }
    else {
	this->parent.reset();
    }
}

std::shared_ptr<fls::IFile> fls::File::getParent() const {
    return this->parent.lock();
}