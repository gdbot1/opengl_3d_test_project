#pragma once

#include <chrono>
#include <stdexcept>

namespace t {

template<typename T>
inline long long time() {
    return std::chrono::duration_cast<T>(
	std::chrono::high_resolution_clock::now().time_since_epoch()
    ).count();
}

template<typename T>
inline long long cast(long long nanos) {
    return std::chrono::duration_cast<T>(std::chrono::nanoseconds(nanos)).count();
}

inline long long tpsToDelayInNS(float tps) {
    if (tps == 0) {
	throw std::runtime_error("TIMER ERROR: tpsToDelayInNS(tps) error: tps == 0 (divide to 0 is error at formula 'ns / tps')");
    }

    return static_cast<long long>(1000000000 / tps);
}

}