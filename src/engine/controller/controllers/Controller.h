#pragma once

#include <memory>
#include <string>

#include "engine/controller/IController.h"

#include "utils/file/files/File.h"
#include "utils/file/type/Type.h"

class Controller : public IController, public fls::File {
public:
    Controller(const std::string &name);

    Controller(const std::string &name, std::shared_ptr<fls::IFolder> root);

    virtual ~Controller() = default;

    virtual void setRoot(std::shared_ptr<fls::IFolder> root) override;

    virtual std::shared_ptr<fls::IFolder> getRoot() const override;
protected:
    std::shared_ptr<fls::IFolder> root;
};