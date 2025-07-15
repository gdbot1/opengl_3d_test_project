#include "UpdateDispatcher.h"

UpdateDispatcher::UpdateDispatcher() {

}

void UpdateDispatcher::onUpdate(UpdateContext &context) {
    for (int i = 0; i < listeners.size(); i++) {
	if (listeners[i] == nullptr) {//удаление пустых слушателей
	    listeners.erase(listeners.begin() + i);

	    i--;

	    continue;
	}

	listeners[i]->onUpdate(listeners[i]->getDelay(context));
    }
}