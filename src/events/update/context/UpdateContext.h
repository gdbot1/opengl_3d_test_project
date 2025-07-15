#pragma once

class UpdateContext {
public:
    float dynamic_delta_time, static_delta_time;

    UpdateContext(float dynamic_delta_time, float static_delta_time);

    virtual ~UpdateContext() = default;
};