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
static bool animationEnabled = true;
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
    // #ifdef TESTMODE
    //     return 0;
    // #endif

    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Wait for renderdoc to start and be ready to capture the output

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
    renderer->initialize();

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
        std::println("toggle animation");
        animationEnabled = !animationEnabled; }, std::function<void(int, int, void *)>()));

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
    windows.addMouseEvent(new MouseEvent([&lastX, &lastY](double x, double y, void *userData){
        if (camControl)
        {
            camControl->processMouseMovement(x - lastX, y - lastY);
        }
        lastX = x;
        lastY = y; }, 
        [&windows](int button, int action, int mods, void *userData) {
            if(button == GLFW_MOUSE_BUTTON_1)
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

    // create tests objects
    /*TriangleTest triangleTest;
    triangleTest.setPosition({0.5f, 0.5f, -1.f});
    triangleTest.setScale({SCR_WIDTH / 2, SCR_HEIGHT / 2, 1.f});

    Square square;
    square.setPosition({2, 2, 1});
    square.setScale({1, 1, 1});

    Cube cube;
    cube.setPosition({400, 300, -200});
    cube.setScale({100, 100, 100});

    square.setParent(&cube);

    Font font("./test/FreeSans.ttf");
    Text text(&font, "hello world\nboo");
    text.setPosition({200, 75, -200});
    text.setScale({50, 50, 1});
    text.setColor(ConstColor::Yellow);

    Model basicModel;
    basicModel.open("test/model/Untitled.obj");
    basicModel.setPosition({300, 100, -150});
    basicModel.setScale({50.0f, 50.0f, 50.0f});
    basicModel.setRotation({45.0f, 45.0f, 0.0f});

    Model advancedModel;
    stbi_set_flip_vertically_on_load(false);
    advancedModel.open("test/WeaponSet/objfiles/Untitled.obj");
    advancedModel.setPosition({600, 400, -300});
    advancedModel.setScale(glm::vec3(2));
    advancedModel.setRotation({90.0f, 0.0f, 0.0f});*/

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
    std::map<std::string, std::string> ShaderDefines;
    ShaderProgram textShaderProgram("text_shader.shader", &ShaderDefines);
    // create a default material
    Material material = Material();
    material.albedo.emplace<Texture>().load("test/img.png");
    material.metallic = 0.0f;
    material.roughness = 1.0f;

    // render_state.push_back(DrawCall(&triangleTest));
    // render_state.push_back(DrawCall(&square));
    // render_state.push_back(DrawCall(&cube));
    // render_state.push_back(DrawCall(&text, &textShaderProgram));
    // render_state.push_back(DrawCall(&basicModel));
    // render_state.push_back(DrawCall(&advancedModel));
    render_state.push_back(DrawCall(&sponzaModel));

    // assign the material to each draw call
    for (auto &&i : render_state)
    {
        // i.material = &material;
        forwardGeometry->pushDrawCall(&i);
    }

    // create a point light
    PointLight pointLight;
    pointLight.setPosition({600, 400, 50});
    pointLight.setColor(ConstColor::Red);
    pointLight.setRange(10000.0f);
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
        if (!animationEnabled)
        {
            updateGeometry(render_state);
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