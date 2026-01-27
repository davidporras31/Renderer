#include <print>
#include "../include/Test.hpp"
#include "../include/Renderer.h"
#include "../include/stage/ForwardGeometry.h"
#include "../include/stage/DebugRender.h"
#include <GLFW/glfw3.h>
#include "TriangleTest.h"
#include "../include/OrthographicCamera.h"
#include "../include/ShaderProgram.h"
#include "../include/Texture.h"
#include "../include/Square.h"
#include "../include/Cube.h"
#include "../include/Text.h"
#include "../include/Model.h"
#include "../include/lights/PointLight.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

static Renderer *renderer;

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

        OrthographicCamera camera(0.f, SCR_WIDTH, 0.f, SCR_HEIGHT, 0.1f, 500.0f);
        camera.setPosition({0, 0, -2});
        forwardGeometry->setCamera(&camera);

        // create shader programs for test rendering
        ShaderProgram textShaderProgram("text_shader",
                                        {{FORWARDGEOMETRY_SHADER_PATH ".vs", GL_VERTEX_SHADER},
                                         {"test/text.fs", GL_FRAGMENT_SHADER}},
                                        "./shaders");
        // create a default material
        Material material = Material();
        material.albedo.emplace<Texture>().load("test/img.png");
        material.metallic = 0.5f;
        material.roughness = 0.5f;
        material.ao = 1.0f;


        render_state.push_back(DrawCall(&square));
        render_state.push_back(DrawCall(&cube));
        render_state.push_back(DrawCall(&triangleTest));
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
        pointLight.setPosition({600, 400, 150});
        pointLight.setColor(ConstColor::White);
        pointLight.setRange(600.0f);
        forwardGeometry->addLight(&pointLight);

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

            // prepare for next frame
            for (auto &&i : render_state)
            {
                forwardGeometry->pushDrawCall(&i);
            }
            forwardGeometry->addLight(&pointLight);
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

bool keyPressed = false;
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
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        keyPressed = true;
    }
    else if (keyPressed)
    {
        debugMode++;
        if ((debugMode % 4 == 0 || debugMode % 4 == 1) && keyPressed)
        {
            std::println("debug graphics");
            bool current = renderer->getDebugMode("ForwardGeometry");
            renderer->setDebugMode("ForwardGeometry", !current);
            keyPressed = false;
        }
        if ((debugMode % 4 == 2 || debugMode % 4 == 3) && keyPressed)
        {
            std::println("debug lights");
            ForwardGeometry* fg = static_cast<ForwardGeometry*>(renderer->getStage("ForwardGeometry"));
            bool current = fg->getDebugLightMode();
            fg->setDebugLightMode(!current);
            keyPressed = false;
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