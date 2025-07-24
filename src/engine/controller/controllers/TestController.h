#pragma once

#include <iostream>
#include <string>

#include "engine/controller/controllers/Controller.h"

class TestController : public Controller {
public:
    TestController(const std::string &name);

    void run() override;
};