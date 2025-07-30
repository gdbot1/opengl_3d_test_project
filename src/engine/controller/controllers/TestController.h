#pragma once

#include <iostream>
#include <string>

#include "engine/controller/controllers/Controller.h"

#include "graphics/elements/window/Window.h"

#include "utils/file/utils/FileUtils.h"
#include "utils/file/files/Any.h"

class TestController : public Controller {
public:
    TestController(const std::string &name);

    void run() override;
};