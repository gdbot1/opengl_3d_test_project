#pragma once

#include <iostream>

#include "engine/controller/Controller.h"

class TestController : public Controller {
public:
    TestController();

    virtual void run() override;

    virtual void update() override;
};