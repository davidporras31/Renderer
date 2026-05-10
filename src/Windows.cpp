
#include "../include/Windows.h"

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
