#include "DynamicUpdatable.h"

float DynamicUpdatable::getDelay(UpdateContext &context) const {
    return context.dynamic_delta_time;
}