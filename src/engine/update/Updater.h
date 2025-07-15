#pragma once

#include "events/update/UpdateDispatcher.h"

#include "utils/time/Timer.h"//подтягивает TimerUtils автоматически

//можно добавить динамический tps, для этого надо менять его с delay

class Updater : public UpdateDispatcher {
public:
    Updater(float tps);

    virtual ~Updater() = default;

    void start();

    void stop();

    float getTps() const;
private:
    float tps;
    long long delay;
    t::Timer timer;
    bool active;

    void loop();
};