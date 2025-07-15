#pragma once

#include "TimeUtils.h"

namespace t {

class Timer {
public:
    Timer();

    virtual ~Timer() = default;

    void load();

    bool checkDelay(long long delay);//delay - is a delta_time

    long long getDeltaTime() const;
private:
    long long last_time, delta_time;
};

}