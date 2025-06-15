#include "KeyDispatcher.h"

callback::KeyDispatcher::KeyDispatcher() {

}

void callback::KeyDispatcher::onKeyEvent(KeyEvent &event) {
    for (int i = 0; i < listeners.size(); i++) {
	if (listeners[i] == nullptr) {
	    listeners.erase(listeners.begin() + i);

	    i--;

	    continue;
	}

	listeners[i]->onKeyEvent(event);
    }
}