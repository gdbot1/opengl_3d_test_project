#pragma once

#include "utils/file/IFile.h"
#include "engine/controller/IRunnable.h"
#include "engine/controller/IRootable.h"

class IController : virtual public fls::IFile, public IRunnable, public IRootable {
};