#include "TestController.h"

TestController::TestController(const std::string &name) : Controller(name) {

}

void TestController::run() {
    std::cout << "TestController is started with .run(). Controller is inside of: " << this->root->getName() << std::endl;
    std::cout << "Folder contains: " << this->root->getFiles().size() << " elements" << std::endl;
}