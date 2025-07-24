#pragma once

#include <memory>

#include "Folder.h"

#include "utils/file/utils/FileUtils.h"

#include "engine/controller/IRootable.h"

namespace fls {

class RootFolder : public fls::Folder {
public:
    void add(std::shared_ptr<fls::IFile> file) override;

    virtual ~RootFolder() = default;
};

}