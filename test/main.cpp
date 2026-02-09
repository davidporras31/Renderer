#include <print>
#include "../include/Test.hpp"
#include "../include/Renderer.h"
#include "../include/stage/ForwardGeometry.h"
#include "../include/stage/DebugRender.h"
#include <GLFW/glfw3.h>
#include "TriangleTest.h"
#include "CSVLoader.h"
#include "../include/OrthographicCamera.h"
#include "../include/ShaderProgram.h"
#include "../include/Texture.h"
#include "../include/Square.h"
#include "../include/Cube.h"
#include "../include/Text.h"
#include "../include/Model.h"
#include "../include/lights/PointLight.h"
#include "../include/lights/DirectionalLight.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

static Renderer *renderer;
static bool animationEnabled = true;
static glm::vec3 camRotation = {0, 0, 0};

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
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    {
        // glfw window creation
        // --------------------
        GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::println("Failed to create GLFW window");
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // start the renderer
        renderer = new Renderer((GLADloadfunc)glfwGetProcAddress);
        renderer->setClearColor(ConstColor::Dark_Modern_Gray);

        // set up the rendering stages
        ForwardGeometry *forwardGeometry = new ForwardGeometry();
        DebugRender *debugRender = new DebugRender();
        renderer->addStage(forwardGeometry);
        renderer->addStage(debugRender);
        renderer->initialize();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // create tests objects
        TriangleTest triangleTest;
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
        advancedModel.setRotation({90.0f, 0.0f, 0.0f});

        std::vector<DrawCall> render_state;

        Transformable camOrigin;
        camOrigin.setPosition({0, 0, 0});
        camOrigin.setRotation({0, 0, 0});
        camOrigin.setScale({1, 1, 1});

        OrthographicCamera camera(0.f, SCR_WIDTH, 0.f, SCR_HEIGHT, 0.1f, 500.0f);
        camera.setPosition({0, 0, -2});
        // camera.setParent(&camOrigin);
        forwardGeometry->setCamera(&camera);

        // create shader programs for test rendering
        ShaderProgram textShaderProgram("text_shader",
                                        {{FORWARDGEOMETRY_SHADER_PATH ".vs", GL_VERTEX_SHADER},
                                         {"test/text.fs", GL_FRAGMENT_SHADER}},
                                        "./shaders");
        // create a default material
        Material material = Material();
        material.albedo.emplace<Texture>().load("test/img.png");
        material.metallic = 0.0f;
        material.roughness = 0.0f;
        material.ao = 1.0f;

        render_state.push_back(DrawCall(&triangleTest));
        render_state.push_back(DrawCall(&square));
        render_state.push_back(DrawCall(&cube));
        render_state.push_back(DrawCall(&text, &textShaderProgram));
        render_state.push_back(DrawCall(&basicModel));
        render_state.push_back(DrawCall(&advancedModel));

        // assign the material to each draw call
        for (auto &&i : render_state)
        {
            i.material = &material;
            forwardGeometry->pushDrawCall(&i);
        }

        // create a point light
        PointLight pointLight;
        pointLight.setPosition({600, 400, 50});
        pointLight.setColor(ConstColor::White);
        pointLight.setRange(10000.0f);
        forwardGeometry->addLight(&pointLight);

        DirectionalLight dirLight;
        dirLight.setDirection({-1, -1, -1});
        dirLight.setColor(ConstColor::White);
        forwardGeometry->addLight(&dirLight);

        std::vector<Light *> lights =
            {
                &pointLight,
                &dirLight};

        // render loop
        // -----------
        while (!glfwWindowShouldClose(window))
        {
            // input
            // -----
            processInput(window);

            renderer->clear();

            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            ypos = abs(ypos - SCR_HEIGHT);
            pointLight.setPosition(glm::vec3(xpos, ypos, -50));
            glm::vec3 rot = triangleTest.getRotation();
            rot.z += 0.005f;
            triangleTest.setRotation(rot);
            rot = cube.getRotation();
            rot.x += 0.002f;
            rot.y += 0.003f;
            cube.setRotation(rot);

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

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    delete renderer;
    glfwTerminate();
    return 0;
}

bool keyQPressed = false;
bool keyEPressed = false;
int debugMode = -1;
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        std::println("capture");
        renderer->captureScreenshot("./test.png", GL_RGBA);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        keyEPressed = true;
    }
    else if (keyEPressed)
    {
        keyEPressed = false;
        std::println("toggle animation");
        animationEnabled = !animationEnabled;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        keyQPressed = true;
    }
    else if (keyQPressed)
    {
        debugMode++;
        if ((debugMode % 4 == 0 || debugMode % 4 == 1) && keyQPressed)
        {
            std::println("debug graphics");
            bool current = renderer->getDebugMode("ForwardGeometry");
            renderer->setDebugMode("ForwardGeometry", !current);
            keyQPressed = false;
        }
        if ((debugMode % 4 == 2 || debugMode % 4 == 3) && keyQPressed)
        {
            std::println("debug lights");
            ForwardGeometry *fg = static_cast<ForwardGeometry *>(renderer->getStage("ForwardGeometry"));
            bool current = fg->getDebugLightMode();
            fg->setDebugLightMode(!current);
            keyQPressed = false;
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.

    renderer->setViewport({0, 0, width, height});
}