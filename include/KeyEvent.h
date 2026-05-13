
#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <functional>

class KeyEvent
{
private:
    int key;
    std::function<void(int, int, void *)> pressCallback;
    std::function<void(int, int, void *)> releaseCallback;
    std::function<void(int, int, void *)> holdCallback;
    void *userData;
    bool hold;
public:
    KeyEvent(int key, std::function<void(int, int, void *)> pressCallback, void *userData = nullptr);
    KeyEvent( int key, std::function<void(int, int, void *)> pressCallback, std::function<void(int, int, void *)> releaseCallback, std::function<void(int, int, void *)> holdCallback, void *userData = nullptr);
    ~KeyEvent();

    void onPress(int scancode, int mods);
    void onRelease(int scancode, int mods);
    void onHold(int scancode, int mods);

    bool isHolded() const;
    int getKey() const;
};

#endif // KEYEVENT_H
