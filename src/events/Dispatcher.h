#pragma once

#include <vector>

template<typename L>
class Dispatcher {
public:
    Dispatcher() = default;

    ~Dispatcher() = default;

    void addListener(L* l) {
	listeners.push_back(l);
    }

    L* getListener(int i) const {
	if (i < 0 || i >= listeners.size()) {
	    throw runtime_error("DISPATCER ERROR: At 'getListener(int i)': Index i out of ranges of listeners list'");	
	}

	return listeners[i];
    }

    void removeListener(int i) {
	if (i < 0 || i >= listeners.size()) {
	    throw runtime_error("DISPATCER ERROR: At 'removeListener(int i)': Index i out of ranges of listeners list'");
	}

	listeners.erase(listeners.begin() + i);
    }

    void removeListener(L* l) {
	listeners.erase(std::remove(listeners.begin(), listeners.end(), l), listeners.end());
    }
protected:
    std::vector<L*> listeners;
};