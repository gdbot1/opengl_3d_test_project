#pragma once

#include "Updatable.h"

class DynamicUpdatable : public Updatable {
public:
    virtual ~DynamicUpdatable() = default;

    virtual float getDelay(UpdateContext &context) const override;
};  