#pragma once

#include "events/Dispatcher.h"
#include "listeners/Updatable.h"
#include "context/UpdateContext.h"

class UpdateDispatcher : public Dispatcher<Updatable> {
public:
    UpdateDispatcher();

    virtual ~UpdateDispatcher() = default;

    virtual void onUpdate(UpdateContext &context);
};