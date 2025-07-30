#pragma once

#include <memory>
#include <string>

#include "File.h"

namespace fls {

template<typename T>
class Any : public fls::File {
public:
    Any(const std::shared_ptr<T>& object, const std::string &name) : fls::File(name, fls::Type::Unknown), object(object) {}

    Any(const std::shared_ptr<T>& object, const std::string &name, fls::Type type) : fls::File(name, type), object(object) {}

    virtual ~Any() = default;

    std::shared_ptr<T> get() const {
	return this->object;
    }
private:
    std::shared_ptr<T> object;
};

}