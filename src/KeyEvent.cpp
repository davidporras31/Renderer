
#include "../include/KeyEvent.h"

KeyEvent::KeyEvent( int key, std::function<void(int, int, void *)> pressCallback, std::function<void(int, int, void *)> releaseCallback, std::function<void(int, int, void *)> repeatCallback, void *userData)
    : key(key), pressCallback(pressCallback), releaseCallback(releaseCallback), repeatCallback(repeatCallback), userData(userData)
{
    
}

KeyEvent::~KeyEvent() {
    
}

void KeyEvent::onPress(int scancode, int mods) {
    if (pressCallback) {
        pressCallback(scancode, mods, userData);
    }
}

void KeyEvent::onRelease(int scancode, int mods) {
    if (releaseCallback) {
        releaseCallback(scancode, mods, userData);
    }
}

void KeyEvent::onRepeat(int scancode, int mods) {
    if (repeatCallback) {
        repeatCallback(scancode, mods, userData);
    }
}

int KeyEvent::getKey() const
{
    return key;
}