#pragma once

#include <string>

#include "type/Type.h"

namespace fls {

class File {
public:
    File(const std::string &name, fls::Type type);

    virtual ~File();

    virtual std::string getName() const;

    virtual fls::Type getType() const;
private:
    std::string name;
    fls::Type type;
};

}