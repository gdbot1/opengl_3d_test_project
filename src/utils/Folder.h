#include "GenericFolder.h"

#include <any>

class Folder : public GenericFolder<std::any> {
public:
    Folder() = default;
};