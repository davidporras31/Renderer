
#include "../include/MouseEvent.h"

MouseEvent::MouseEvent( std::function<void(double, double, void*)> mouseMovedCallback, std::function<void(int, int, int, void*)> mouseButtonCallback, void* userData)
    : mouseMovedCallback(mouseMovedCallback), mouseButtonCallback(mouseButtonCallback), userData(userData) {
    
}

MouseEvent::~MouseEvent() {
    
}

void MouseEvent::onMouseMoved(double x, double y) {
    if (mouseMovedCallback) {
        mouseMovedCallback(x, y, userData);
    }
}

void MouseEvent::onMouseButton(int button, int action, int mods) {
    if (mouseButtonCallback) {
        mouseButtonCallback(button, action, mods, userData);
    }
}
