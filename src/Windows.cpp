
#include "../include/Windows.h"

void Windows::framebufferSizeCallback(int width, int height)
{
    renderer->setViewport(glm::ivec4(0, 0, width, height));
}

void Windows::mouseMovementCallback(double xpos, double ypos)
{
    for (size_t i = 0; i < mouseEvents.getSize(); i++)
    {
        mouseEvents[i]->onMouseMoved(xpos, ypos);
    }
}

void Windows::mouseButtonCallback(int button, int action, int mods)
{
    for (size_t i = 0; i < mouseEvents.getSize(); i++)
    {
        mouseEvents[i]->onMouseButton(button,action,mods);
    }
    
}

void Windows::keyboardInputCallback(int key, int scancode, int action, int mods)
{
    for (size_t i = 0; i < keyEvents.getSize(); i++)
    {
        if (key == keyEvents[i]->getKey())
        {
            switch (action)
            {
            case GLFW_PRESS:
                keyEvents[i]->onPress(scancode,mods);
                break;
            case GLFW_RELEASE:
                keyEvents[i]->onRelease(scancode,mods);
                break;
            default:
                break;
            }
        }
        
    }
    
}

Windows::Windows(const std::string &title, const Parameters &params)
    : windowSize(params.windowWidth, params.windowHeight), frameTimeLimit(1.0 / params.frameRateLimit), lastFrameTime(0), currentFrameTime(0)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_DECORATED, params.borderlessWindowEnabled ? GLFW_FALSE : GLFW_TRUE);
    window = glfwCreateWindow(windowSize.x, windowSize.y, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, (GLFWframebuffersizefun)[](GLFWwindow *window, int width, int height) {
        static_cast<Windows *>(glfwGetWindowUserPointer(window))->framebufferSizeCallback(width, height);
    });
    glfwSetCursorPosCallback(window, (GLFWcursorposfun)[](GLFWwindow *window, double xpos, double ypos) {
        static_cast<Windows *>(glfwGetWindowUserPointer(window))->mouseMovementCallback(xpos, ypos);
    });
    glfwSetMouseButtonCallback(window,(GLFWmousebuttonfun)[](GLFWwindow* window, int button, int action, int mods) {
        static_cast<Windows *>(glfwGetWindowUserPointer(window))->mouseButtonCallback(button, action, mods);
    });
    glfwSetKeyCallback(window, (GLFWkeyfun)[](GLFWwindow *window, int key, int scancode, int action, int mods) {
        static_cast<Windows *>(glfwGetWindowUserPointer(window))->keyboardInputCallback(key, scancode, action, mods);
    });
    glfwSwapInterval(params.vsyncEnabled ? 1 : 0);
    setFullscreen(params.fullscreenEnabled);
    renderer = new Renderer((GLADloadfunc)glfwGetProcAddress);
}

Windows::~Windows()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Windows::isOpen() const
{
    return !glfwWindowShouldClose(window);
}

void Windows::close()
{
    glfwSetWindowShouldClose(window, true);
}

void Windows::clear()
{
    renderer->clear();
    currentFrameTime = glfwGetTime();
}

void Windows::drawAll()
{
    renderer->renderFrame();
}

void Windows::swapBuffersAndPollEvents()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
    for (size_t i = 0; i < keyEvents.getSize(); i++)
    {
        if(keyEvents[i]->isHolded())
            keyEvents[i]->onHold(0,0);
    }
    
    // Limit FPS
    double frameTime = glfwGetTime() - currentFrameTime;
    if (frameTime < frameTimeLimit)
    {
        lastFrameTime = std::min(currentFrameTime, frameTimeLimit);
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>((frameTimeLimit - frameTime))));
    }
}

void Windows::setTitle(const std::string &title)
{
    glfwSetWindowTitle(window, title.c_str());
}

void Windows::setSize(const glm::ivec2 &size)
{
    windowSize = size;
    glfwSetWindowSize(window, windowSize.x, windowSize.y);
}

void Windows::setFullscreen(bool fullscreen)
{
    if (fullscreen)
    {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
    }
    else
    {
        // Restaurer taille et position précédents
        glfwSetWindowMonitor(window, nullptr, 0, 0, this->windowSize.x, this->windowSize.y, GLFW_DONT_CARE);
    }
}

void Windows::setCaptureMouse(bool capture)
{
    if (capture)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}
void Windows::addKeyEvent(KeyEvent* keyEvent)
{
    keyEvents.pushBack(keyEvent);
}
void Windows::removeKeyEvent(KeyEvent* keyEvent)
{
    for (size_t i = 0; i < keyEvents.getSize(); i++)
    {
        if (keyEvents[i] == keyEvent)
        {
            keyEvents.remove(i);
            break;
        }
    }
}
void Windows::addMouseEvent(MouseEvent* mouseEvent)
{
    mouseEvents.pushBack(mouseEvent);
}
void Windows::removeMouseEvent(MouseEvent* mouseEvent)
{
    for (size_t i = 0; i < mouseEvents.getSize(); i++)
    {
        if (mouseEvents[i] == mouseEvent)
        {
            mouseEvents.remove(i);
            break;
        }
    }
}
Renderer *Windows::getRenderer() const
{
    return renderer;
}