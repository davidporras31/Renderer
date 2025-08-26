#pragma once

class Renderer {
public:
    Renderer();
    ~Renderer();

    void setViewport();
    void render();
    void clear();
    void setCamera();
    void captureScreenshot();
    void draw();
    void display();
    void resize();
};