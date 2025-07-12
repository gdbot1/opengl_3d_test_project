#pragma once

#include <memory>

#include "IController.h"
#include "utils/Storage.h"

class Controller : public IController {
public:
    Controller();

    Controller(std::shared_ptr<Storage> storage);

    virtual ~Controller() = default;

    virtual void run() override = 0;

    virtual void update() override = 0;

    virtual void setStorage(std::shared_ptr<Storage> storage);

    std::shared_ptr<Storage> getStorage() const;
protected:
    std::shared_ptr<Storage> storage;
};