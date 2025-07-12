#include "Controller.h"

Controller::Controller() {

}

Controller::Controller(std::shared_ptr<Storage> storage) {
    this->storage = storage;
}

void Controller::setStorage(std::shared_ptr<Storage> storage) {
    this->storage = storage;
}

std::shared_ptr<Storage> Controller::getStorage() const {
    return this->storage;
}