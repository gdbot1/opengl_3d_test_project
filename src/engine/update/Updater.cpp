









#include "Updater.h"

Updater::Updater(float tps) : tps(tps) {
    this->delay = t::tpsToDelayInNS(tps);//tps to delay in ns
}

void Updater::start() {//start loop, open function for users. Gets permission to start loop in any thread
    timer.load();

    this->active = true;

    this->loop();
}

void Updater::stop() {
    this->active = false;
}

void Updater::loop() {
    while(this->active) {
	if (timer.checkDelay(this->delay)) {
	    long long delta_time_ns = timer.getDeltaTime();

	    float delta_time = delta_time_ns / 1000000000.0f;

	    float static_delta_time = this->delay / 1000000000.0f;

	    UpdateContext context(delta_time, static_delta_time);//dymanic, static (dynamic - real delay, static - math delay)

	    onUpdate(context);//функция UpdateDispatcher
	}
    }
}

float Updater::getTps() const {
    return this->tps;
}