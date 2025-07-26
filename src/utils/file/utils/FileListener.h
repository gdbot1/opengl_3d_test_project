#pragma once

#include <memory>
#include <stack>
#include <utility>

#include "utils/file/files/IFolder.h"

namespace fls {

class FileListener {
public:
    virtual ~FileListener() = default;

    virtual void onFile(std::shared_ptr<fls::IFile> file, std::stack<std::pair<std::shared_ptr<fls::IFolder>, int>> stack) = 0;
};

}