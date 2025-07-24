#pragma once

#include <string>
#include <memory>

#include "utils/file/IFile.h"
#include "utils/file/files/IFolder.h"

namespace fls {

class File : public virtual fls::IFile, public std::enable_shared_from_this<fls::File> {
public:
    File(const std::string &name, fls::Type type);

    virtual ~File();

    virtual std::string getName() const override;

    virtual fls::Type getType() const override;

    virtual void setParent(std::shared_ptr<fls::IFile> parent) override;

    virtual std::shared_ptr<fls::IFile> getParent() const override;
private:
    std::string name;
    fls::Type type;
    std::weak_ptr<fls::IFolder> parent;
};

}