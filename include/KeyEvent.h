
#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <functional>

class KeyEvent
{
private:
    int key;
    void *userData;
    std::function<void(int, int, void *)> pressCallback;
    std::function<void(int, int, void *)> releaseCallback;
    std::function<void(int, int, void *)> repeatCallback;
public:
    KeyEvent( int key, std::function<void(int, int, void *)> pressCallback, std::function<void(int, int, void *)> releaseCallback, std::function<void(int, int, void *)> repeatCallback, void *userData = nullptr);
    ~KeyEvent();

    void onPress(int scancode, int mods);
    void onRelease(int scancode, int mods);
    void onRepeat(int scancode, int mods);

    int getKey() const;
};

#endif // KEYEVENT_H
