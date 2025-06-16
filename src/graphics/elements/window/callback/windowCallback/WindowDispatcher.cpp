#include "WindowDispatcher.h"

callback::WindowDispatcher::WindowDispatcher() {

}

void callback::WindowDispatcher::onFramebufferSizeEvent(FramebufferSizeEvent &event) {
    for (int i = 0; i < listeners.size(); i++) {
	if (listeners[i] == nullptr) {
	    listeners.erase(listeners.begin() + i);

	    i--;

	    continue;
	}

	listeners[i]->onFramebufferSizeEvent(event);
    }
}