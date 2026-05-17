#include <print>
#include <thread>
#include <chrono>
#include "../include/Windows.h"
#include "../include/Test.hpp"
#include "../include/stage/ForwardGeometry.h"
#include "../include/stage/DebugRender.h"
#include "TriangleTest.h"
#include "CSVLoader.h"
#include "CamControl.h"
#include "../include/PerspectiveCamera.h"
#include "../include/ShaderProgram.h"
#include "../include/Texture.h"
#include "../include/Square.h"
#include "../include/Cube.h"
#include "../include/Text.h"
#include "../include/Model.h"
#include "../include/lights/PointLight.h"
#include "../include/lights/DirectionalLight.h"

void processMouseMovement(GLFWwindow *window, double xpos, double ypos);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

static Renderer *renderer;
static bool reload_transform = true;
static CamControl *camControl;

static CSVFile csvFile("../test/geometry.csv");
void updateGeometry(std::vector<DrawCall> &render_state)
{
    csvFile.update();
    for (size_t i = 0; i < render_state.size(); i++)
    {
        // Update each draw call with the latest geometry data
        Transformable *transform = (Transformable *)render_state[i].drawable;
        glm::vec3 newPosition = glm::vec3(
            std::stof(csvFile.getData()[i][0]),
            std::stof(csvFile.getData()[i][1]),
            std::stof(csvFile.getData()[i][2]));
        glm::vec3 newRotation = glm::vec3(
            std::stof(csvFile.getData()[i][3]),
            std::stof(csvFile.getData()[i][4]),
            std::stof(csvFile.getData()[i][5]));
        glm::vec3 newScale = glm::vec3(
            std::stof(csvFile.getData()[i][6]),
            std::stof(csvFile.getData()[i][7]),
            std::stof(csvFile.getData()[i][8]));
        transform->setPosition(newPosition);
        transform->setRotation(newRotation);
        transform->setScale(newScale);
    }
}

int main()
{
#ifdef TESTMODE
    return 0;
#endif

    Parameters params;
    Windows windows("Mon Jeu", params);
    // start the renderer
    renderer = windows.getRenderer();
    renderer->setClearColor(ConstColor::Dark_Modern_Gray);

    // set up the frame buffers
    // renderer->addFrameBuffer(new FrameBuffer(), "MainFrameBuffer");// TODO add more frame buffers for different rendering stages
    // set up the rendering stages
    ForwardGeometry *forwardGeometry = new ForwardGeometry();
    DebugRender *debugRender = new DebugRender();
    renderer->addStage(forwardGeometry);
    renderer->addStage(debugRender);
    renderer->initialize(params);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    windows.addKeyEvent(new KeyEvent(GLFW_KEY_ESCAPE, [&windows](int scancode, int mods, void *userData)
                                     { windows.close(); }));

    windows.addKeyEvent(new KeyEvent(GLFW_KEY_ENTER, [](int scancode, int mods, void *userData)
                                     {
        std::println("capture");
        renderer->captureScreenshot("./test.png", GL_RGBA); }));

    windows.addKeyEvent(new KeyEvent(GLFW_KEY_E, std::function<void(int, int, void *)>(), [](int scancode, int mods, void *userData)
                                     {
        std::println("Reload all transforms");
        reload_transform = !reload_transform; 
    }, std::function<void(int, int, void *)>()));

    int debugMode = -1;

    windows.addKeyEvent(new KeyEvent(GLFW_KEY_Q, [&debugMode](int scancode, int mods, void *userData)
                                     {
        debugMode++;
        if ((debugMode % 4 == 0 || debugMode % 4 == 1))
        {
            std::println("debug graphics");
            bool current = renderer->getDebugMode("ForwardGeometry");
            renderer->setDebugMode("ForwardGeometry", !current);
        }
        if ((debugMode % 4 == 2 || debugMode % 4 == 3))
        {
            std::println("debug lights");
            ForwardGeometry *fg = static_cast<ForwardGeometry *>(renderer->getStage("ForwardGeometry"));
            bool current = fg->getDebugLightMode();
            fg->setDebugLightMode(!current);
        } }));

    double lastX = 0, lastY = 0;
    windows.addMouseEvent(new MouseEvent([&lastX, &lastY](double x, double y, void *userData)
                                         {
        if (camControl)
        {
            camControl->processMouseMovement(x - lastX, y - lastY);
        }
        lastX = x;
        lastY = y; },
                                         [&windows](int button, int action, int mods, void *userData)
                                         {
                                             if (button == GLFW_MOUSE_BUTTON_1)
                                                 switch (action)
                                                 {
                                                 case GLFW_PRESS:
                                                     camControl->setClicked(true);
                                                     windows.setCaptureMouse(true);
                                                     break;
                                                 case GLFW_RELEASE:
                                                     camControl->setClicked(false);
                                                     windows.setCaptureMouse(false);
                                                     break;
                                                 }
                                         }));
    windows.addKeyEvent(new KeyEvent(GLFW_KEY_W, std::function<void(int, int, void *)>(), std::function<void(int, int, void *)>(), [](int scancode, int mods, void *userData)
                                     { camControl->moveCamera({0, 1}); }));
    windows.addKeyEvent(new KeyEvent(GLFW_KEY_S, std::function<void(int, int, void *)>(), std::function<void(int, int, void *)>(), [](int scancode, int mods, void *userData)
                                     { camControl->moveCamera({0, -1}); }));
    windows.addKeyEvent(new KeyEvent(GLFW_KEY_A, std::function<void(int, int, void *)>(), std::function<void(int, int, void *)>(), [](int scancode, int mods, void *userData)
                                     { camControl->moveCamera({1, 0}); }));
    windows.addKeyEvent(new KeyEvent(GLFW_KEY_D, std::function<void(int, int, void *)>(), std::function<void(int, int, void *)>(), [](int scancode, int mods, void *userData)
                                     { camControl->moveCamera({-1, 0}); }));

    Model sponzaModel;
    sponzaModel.open("test/sponza/sponza.obj");
    sponzaModel.setPosition({0, -1, 0});
    sponzaModel.setScale({0.01f, 0.01f, 0.01f});
    sponzaModel.setRotation({0, 0, 0});

    std::vector<DrawCall> render_state;

    PerspectiveCamera camera(45.0f, static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.5f, 100.0f);
    camera.setPosition({0, 0, -2});
    camControl = new CamControl(&camera);
    forwardGeometry->setCamera(&camera);

    // create shader programs for test rendering
    std::map<std::string, std::string> ShaderDefines = generateParameterMap(params);
    ShaderProgram textShaderProgram("text_shader.shader", &ShaderDefines);
    // create a default material
    Material material = Material();
    material.albedo.emplace<Texture>().load("test/img.png");
    material.metallic = 0.0f;
    material.roughness = 1.0f;
    render_state.push_back(DrawCall(&sponzaModel));

    // assign the material to each draw call
    for (auto &&i : render_state)
    {
        // i.material = &material;
        forwardGeometry->pushDrawCall(&i);
    }

    // create a point light
    PointLight pointLight;
    pointLight.setPosition({0, 1, 0});
    pointLight.setColor(ConstColor::Red);
    pointLight.setRange(10.0f);
    forwardGeometry->addLight(&pointLight);

    DirectionalLight dirLight;
    dirLight.setDirection({1, 1, 1});
    dirLight.setColor(ConstColor::White);
    forwardGeometry->addLight(&dirLight);

    std::vector<Light *> lights =
        {
            &pointLight,
            &dirLight};

    double lastTime = glfwGetTime();
    int nbFrames = 0;
    // render loop
    // -----------
    while (windows.isOpen())
    {
        windows.clear();
        double currentTime = glfwGetTime();

        nbFrames++;

        if (currentTime - lastTime >= 1.0)
        {
            double fps = (double)nbFrames / (currentTime - lastTime);
            char title[256];
            snprintf(title, 256, "Mon Jeu [%.1f FPS]", fps);
            windows.setTitle(title);

            nbFrames = 0;
            lastTime = currentTime;
        }
        renderer->renderFrame();
        if (!reload_transform)
        {
            updateGeometry(render_state);
            reload_transform =false;
        }
        // prepare for next frame
        for (auto &&i : render_state)
        {
            forwardGeometry->pushDrawCall(&i);
        }
        for (auto &&light : lights)
        {
            forwardGeometry->addLight(light);
        }
        forwardGeometry->sendLightData();

        windows.swapBuffersAndPollEvents();
    }
}