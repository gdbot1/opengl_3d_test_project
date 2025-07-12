#pragma once

class IController {
public:
    virtual void run() = 0;

    virtual void update() = 0;
};