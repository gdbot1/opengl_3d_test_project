#pragma once

#include <memory>

#include "utils/file/files/IFolder.h"

class IRootable {
public:
    virtual void setRoot(std::shared_ptr<fls::IFolder> root) = 0;

    virtual std::shared_ptr<fls::IFolder> getRoot() const = 0;
};