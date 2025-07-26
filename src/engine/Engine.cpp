#include "Engine.h"

Engine::Engine(const std::string &name) {
    this->root = std::make_shared<fls::Folder>(name);
}

Engine::Engine(const std::shared_ptr<fls::IFolder> root) : root(root) {

}

void Engine::reg(IRootable &controller) {
    controller.setRoot(this->root);//установка корневой папки для внутренего доступа.
}

void Engine::setRoot(std::shared_ptr<fls::IFolder> root) {
    this->root = root;
}

std::shared_ptr<fls::IFolder> Engine::getRoot() const {
    return this->root;
}

//Углубляясь в папки - стак будет пополнятсья данными folder:id, id - это точка входа, и при возврате можно будет продолжить чтение с той-же точки
void Engine::run() {
    fls::run(root, *this);
}

//private
void Engine::onFile(std::shared_ptr<fls::IFile> file, std::stack<std::pair<std::shared_ptr<fls::IFolder>, int>> stack) {
    if (file->getType() == fls::Type::Controller) {
	std::shared_ptr<IController> controller = fls::cast<fls::IFile, IController>(file);

	if (controller) {
	    std::cout << "Controller is activated: " << file->getName() << std::endl;

	    controller->run();
	}
    }

    std::cout << "file: " << file->getName() << std::endl;
}