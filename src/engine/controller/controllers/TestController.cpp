#include "TestController.h"

TestController::TestController(const std::string &name) : Controller(name) {

}

void TestController::run() {
    std::cout << "TestController is started with .run(). Controller is inside of: " << this->root->getName() << std::endl;
    std::cout << "Folder contains: " << this->root->getFiles().size() << " elements" << std::endl;

    std::shared_ptr<gr::Window> window = fls::getAs<fls::Any<gr::Window>>("window/Window", fls::cast<fls::IFolder, fls::IFile>(this->root))->get();

    std::cout << "Window object has id: " << window->getWindow() << std::endl;
}