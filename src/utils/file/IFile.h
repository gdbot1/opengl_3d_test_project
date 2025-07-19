#pragma once

#include <string>
#include <memory>

#include "type/Type.h"

namespace fls {

class IFile {
public:
    virtual ~IFile() = default;

    virtual std::string getName() const = 0;

    virtual fls::Type getType() const = 0;

    virtual void setParent(std::shared_ptr<fls::IFile> parent) = 0;

    virtual std::shared_ptr<fls::IFile> getParent() const = 0;
};

}