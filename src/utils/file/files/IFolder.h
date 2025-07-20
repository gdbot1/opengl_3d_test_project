#pragma once

#include <memory>

#include "utils/file/IFile.h"
#include "utils/container/IContainer.h"

namespace fls {

class IFolder : public virtual fls::IFile, public IContainer<fls::IFile> {
public:
    template<typename T>
    std::shared_ptr<T> getAs(const std::string &name) {
	std::shared_ptr<IFile> file = get(name);

	if (!file) {
	    return nullptr;
	}

	return std::dynamic_pointer_cast<T>(file);
    }
};

}