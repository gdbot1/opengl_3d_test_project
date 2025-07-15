#include "Timer.h"

t::Timer::Timer() {
    this->load();
}

void t::Timer::load() {
    last_time = t::time<std::chrono::nanoseconds>();
}

bool t::Timer::checkDelay(long long delay) {
    long long current_time = t::time<std::chrono::nanoseconds>();

    long long delta = current_time - last_time;

    if (delta >= delay) {
	last_time = current_time;

	delta_time = delta;

	return true;
    }

    return false;
}

long long t::Timer::getDeltaTime() const {
    return delta_time;
}