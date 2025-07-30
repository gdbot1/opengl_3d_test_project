#include "TestSample.h"

TestSample::TestSample(std::shared_ptr<gr::Window> window, std::shared_ptr<Scene> scene) : window(window), scene(scene) {}

std::shared_ptr<fls::IFolder> TestSample::getRoot() {
    std::shared_ptr<fls::IFolder> root = std::make_shared<fls::Folder>("root");

    std::shared_ptr<fls::IFolder> window_folder = std::make_shared<fls::Folder>("window"), scene_folder = std::make_shared<fls::Folder>("scene"), engine_folder = std::make_shared<fls::Folder>("engine");

    std::shared_ptr<fls::Any<gr::Window>> window = std::make_shared<fls::Any<gr::Window>>(this->window, "Window");
    std::shared_ptr<fls::Any<Scene>> scene = std::make_shared<fls::Any<Scene>>(this->scene, "Scene");

    //root
    root->add(window_folder);
    root->add(scene_folder);
    root->add(engine_folder);

    //window
    window_folder->add(window);

    //scene
    scene_folder->add(scene);

    return root;
}