#include "Updatable.h"

float Updatable::getDelay(UpdateContext &context) const {
    return context.static_delta_time;
}