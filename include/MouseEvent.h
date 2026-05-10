
#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <functional>

class MouseEvent
{
private:
    std::function<void(double, double, void *)> mouseMovedCallback;
    std::function<void(int, int, int, void *)> mouseButtonCallback;
    void *userData;

public:
    MouseEvent(std::function<void(double, double, void *)> mouseMovedCallback, std::function<void(int, int, int, void *)> mouseButtonCallback, void *userData = nullptr);
    ~MouseEvent();

    void onMouseMoved(double x, double y);
    void onMouseButton(int button, int action, int mods);
};

#endif // MOUSEEVENT_H
