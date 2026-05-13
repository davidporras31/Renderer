
#include "../include/KeyEvent.h"

KeyEvent::KeyEvent(int key, std::function<void(int, int, void *)> pressCallback, void *userData)
    : key(key), pressCallback(pressCallback), releaseCallback(nullptr), holdCallback(nullptr), userData(userData), hold(false)
{
}
KeyEvent::KeyEvent(int key, std::function<void(int, int, void *)> pressCallback, std::function<void(int, int, void *)> releaseCallback, std::function<void(int, int, void *)> holdCallback, void *userData)
    : key(key), pressCallback(pressCallback), releaseCallback(releaseCallback), holdCallback(holdCallback), userData(userData), hold(false)
{
}

KeyEvent::~KeyEvent()
{
}

void KeyEvent::onPress(int scancode, int mods)
{
    hold = true;
    if (pressCallback)
    {
        pressCallback(scancode, mods, userData);
    }
}

void KeyEvent::onRelease(int scancode, int mods)
{
    hold = false;
    if (releaseCallback)
    {
        releaseCallback(scancode, mods, userData);
    }
}

void KeyEvent::onHold(int scancode, int mods)
{
    if (holdCallback)
    {
        holdCallback(scancode, mods, userData);
    }
}

bool KeyEvent::isHolded() const
{
    return hold;
}

int KeyEvent::getKey() const
{
    return key;
}