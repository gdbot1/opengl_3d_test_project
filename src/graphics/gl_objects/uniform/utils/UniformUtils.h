#pragma once

#include "graphics/gl_objects/uniform/Uniform.h"

namespace uniform {

template<typename T>
void swap(std::shared_ptr<Uniform<T>> from, std::shared_ptr<Uniform<T>> to) {
    to->setLoc(from->getLoc());
    to->setPath(from->getPath());
    to->setPrefix(from->getPrefix());
    to->setSuffix(from->getSuffix());
}

}