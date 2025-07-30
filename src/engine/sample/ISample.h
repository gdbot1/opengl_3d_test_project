#pragma once

#include <memory>

#include "utils/file/files/IFolder.h"
#include "utils/file/files/folders/Folder.h"

class ISample {
public:
    virtual ~ISample() = default;

    virtual std::shared_ptr<fls::IFolder> getRoot() = 0;
};