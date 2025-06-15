#pragma once

#include "KeyEvent.h"

namespace callback {

class KeyListener {
public:
    KeyListener() = default;

    virtual ~KeyListener() = default;

    virtual void onKeyEvent(callback::KeyEvent &event) = 0;
};

}