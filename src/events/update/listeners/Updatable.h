#pragma once

#include "events/update/context/UpdateContext.h"

class Updatable {
public:
    virtual ~Updatable() = default;

    virtual void onUpdate(float delta_time) = 0;

    virtual float getDelay(UpdateContext &context) const;
};