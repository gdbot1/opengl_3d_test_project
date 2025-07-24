#include "Controller.h"

Controller::Controller(const std::string &name) : fls::File(name, fls::Type::Controller) {

}

Controller::Controller(const std::string &name, std::shared_ptr<fls::IFolder> root) : fls::File(name, fls::Type::Controller) {
    this->root = root;
}

void Controller::setRoot(std::shared_ptr<fls::IFolder> root) {
    this->root = root;
}

std::shared_ptr<fls::IFolder> Controller::getRoot() const {
    return this->root;
}