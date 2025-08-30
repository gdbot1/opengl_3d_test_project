#include "TestUniform.h"

TestUniform::TestUniform(const std::string &path) : Uniform(path) {
    far_uniform = std::make_shared<FloatUniform>("far");
    position_uniform = std::make_shared<Vec3Uniform>("position");
    color_uniform = std::make_shared<Vec3Uniform>("color");

    update();
}

void TestUniform::updateLoc(GLint program) {
    far_uniform->updateLoc(program);
    position_uniform->updateLoc(program);
    color_uniform->updateLoc(program);
}

void TestUniform::uniform() const {
    far_uniform->uniform();
    position_uniform->uniform();
    color_uniform->uniform();
}

void TestUniform::setPath(const std::string &path) {
    Uniform::setPath(path);    

    update();
}

void TestUniform::setPrefix(const std::string &prefix) {
    Uniform::setPrefix(prefix);

    update();
}


void TestUniform::setSuffix(const std::string &suffix) {
    Uniform::setSuffix(suffix);    

    update();
}

void TestUniform::setValue(const TestStruct &value) {
    this->value = value;

    far_uniform->setValue(value.far);
    position_uniform->setValue(value.position);
    color_uniform->setValue(value.color);
}

void TestUniform::update() {
    std::string full_path = this->getFullPath();

    far_uniform->setPrefix(full_path);
    position_uniform->setPrefix(full_path);
    color_uniform->setPrefix(full_path);
}