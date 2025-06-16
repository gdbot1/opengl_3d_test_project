#include "MouseDispatcher.h"

callback::MouseDispatcher::MouseDispatcher() {

}

void callback::MouseDispatcher::onMouseButtonEvent(MouseButtonEvent &event) {
    for (int i = 0; i < listeners.size(); i++) {
	if (listeners[i] == nullptr) {
	    listeners.erase(listeners.begin() + i);

	    i--;

	    continue;
	}

	listeners[i]->onMouseButtonEvent(event);
    }
}