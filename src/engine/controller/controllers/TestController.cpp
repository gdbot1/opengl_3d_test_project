#include "TestController.h"

TestController::TestController() {

}

void TestController::run() {
    std::cout << "TestController is started with .run()" << std::endl;
}

void TestController::update() {
    std::cout << "TestController is updating with .update()" << std::endl;
}