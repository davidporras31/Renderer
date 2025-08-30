#include "Renderer.h"

Renderer::Renderer(GLADloadfunc load)
{
    if (!gladLoadGL(load)) {
        // Handle the error appropriately (e.g., throw an exception, log an error, etc.)
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

Renderer::~Renderer()
{
    
}

void Renderer::setViewport(const glm::i64vec4 viewport)
{
    glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
}

void Renderer::render(Drawable *drawable)
{
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setClearColor(const Color &color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::setCamera(Camera *camera)
{
    this->camera = camera;
}

void Renderer::captureScreenshot(const char *filename)
{
    // Get the viewport dimensions
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int width = viewport[2];
    int height = viewport[3];

    // Allocate memory for the pixel data
    unsigned char* pixels = new unsigned char[width * height * 3]; // 3 bytes for RGB

    // Read the pixel data from the framebuffer
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    // Write the pixel data to a PPM file
    FILE* file = fopen(filename, "wb");
    if (file) {
        fprintf(file, "P6\n%d %d\n255\n", width, height);
        // PPM files store pixels from top to bottom, so we need to flip the image vertically
        for (int y = height - 1; y >= 0; --y) {
            fwrite(pixels + y * width * 3, 3, width, file);
        }
        fclose(file);
    } else {
        // Handle file open error
        throw std::runtime_error("Failed to open file for screenshot");
    }

    // Free the allocated memory
    delete[] pixels;
}
