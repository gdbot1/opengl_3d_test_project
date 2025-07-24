#pragma once

#include "utils/file/IFile.h"

class IController : virtual public fls::IFile {
public:
    virtual void run() = 0;
};