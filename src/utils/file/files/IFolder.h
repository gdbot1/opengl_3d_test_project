#pragma once

#include "utils/file/IFile.h"
#include "utils/container/IContainer.h"

namespace fls {

class IFolder : public virtual fls::IFile, public IContainer<fls::IFile> {
public:

};
}