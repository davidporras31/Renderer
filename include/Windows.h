
#ifndef WINDOWS_H
#define WINDOWS_H

#include <thread>
#include <chrono>
#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Parameters.h"

/// @brief Represents a window in the application. It manages the GLFW window and provides methods for window operations such as clearing, drawing, and setting properties.
/// @example
/// Windows window("My Renderer", parameters);
/// while (window.isOpen()) {
///     window.clear();
///     // Update your scene here
///     window.drawAll();
///     window.swapBuffersAndPollEvents();
/// }
class Windows {
private:
    glm::ivec2 windowSize;
    GLFWwindow *window;
    Renderer *renderer;
    double frameTimeLimit, lastFrameTime, currentFrameTime;
public:
    Windows(const std::string &title, const Parameters &params);
    ~Windows();

    /// @brief Checks if the window is open.
    /// @return True if the window is open; otherwise, false.
    bool isOpen() const;
    /// @brief Closes the window.
    void close();
    /// @brief Clears the window's color and depth buffers, preparing it for a new frame.
    void clear();
    /// @brief Draws the current frame, by executing the rendering loop.
    void drawAll();
    /// @brief Swaps the front and back buffers, displaying the rendered frame on the screen and polling for events. It also limits the frame rate based on the specified FPS limit.
    void swapBuffersAndPollEvents();

    /// @brief Sets the title of the window.
    /// @param title The new title for the window.
    void setTitle(const std::string &title);
    /// @brief Sets the size of the window.
    /// @param size The new size for the window.
    void setSize(const glm::ivec2 &size);
    /// @brief Sets the mouse capture mode for the window.
    /// @param capture If true, the mouse cursor will be captured and hidden; otherwise, it will be released.
    void setCaptureMouse(bool capture);
    /// @brief Sets the fullscreen mode for the window.
    /// @param fullscreen If true, the window will be set to fullscreen; otherwise, it will be windowed.
    void setFullscreen(bool fullscreen);

    /// @brief Gets the renderer associated with the window.
    /// @return A pointer to the Renderer instance.
    Renderer *getRenderer() const;
};

#endif // WINDOWS_H
    