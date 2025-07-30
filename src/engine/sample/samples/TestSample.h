#pragma once

#include "engine/sample/ISample.h"

#include "utils/file/files/Any.h"

#include "graphics/elements/window/Window.h"
#include "world/scene/Scene.h"

class TestSample : public ISample {
public:
    TestSample(std::shared_ptr<gr::Window> window, std::shared_ptr<Scene> scene);

    virtual ~TestSample() = default;

    std::shared_ptr<fls::IFolder> getRoot() override;
private:
    std::shared_ptr<gr::Window> window;
    std::shared_ptr<Scene> scene;
};