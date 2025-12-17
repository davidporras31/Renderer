#include <iostream>
#include "../Renderer.h"
#include "../stage/ForwardGeometry.h"
#include <GLFW/glfw3.h>
#include "TriangleTest.h"
#include "../OrthographicCamera.h"
#include "../ShaderProgram.h"
#include "../Texture.h"
#include "../Square.h"
#include "../Cube.h"
#include "../Text.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

static Renderer* renderer;

int main() {   // glfw: initialize and configure
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
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        renderer = new Renderer((GLADloadfunc)glfwGetProcAddress);
        renderer->setClearColor(ConstColor::Dark_Modern_Gray);

        ForwardGeometry* forwardGeometry = new ForwardGeometry();
        renderer->addStage(forwardGeometry);
        renderer->initialize();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        TriangleTest triangleTest;
        triangleTest.setPosition({0.5f,0.5f,-1.f});
        triangleTest.setScale({SCR_WIDTH/2,SCR_HEIGHT/2,1.f});

        Square square;
        square.setPosition({2,2,1});
        square.setScale({1,1,1});

        Cube cube;
        cube.setPosition({400,300,-200});
        cube.setScale({100,100,100});
        
        square.setParent(&cube);

        Font font("./test/FreeSans.ttf");
        Text text(&font,"hello world\nboo");
        text.setPosition({200,75,-200});
        text.setScale({50,50,1});
        text.setColor(ConstColor::Yellow);

        
        std::vector<DrawCall> render_state;

        OrthographicCamera camera(0.f, SCR_WIDTH, 0.f, SCR_HEIGHT, 0.1f, 500.0f);
        camera.setPosition({0,0,-2});
        forwardGeometry->setCamera(&camera);

        ShaderProgram textShaderProgram("text_shader",
            {
                {FORWARDGEOMETRY_SHADER_PATH".vs", GL_VERTEX_SHADER},
                {"test/text.fs", GL_FRAGMENT_SHADER}
            },
            "./shaders");


        Material material = Material();
        Texture texture;
        texture.load("test/img.png");
        material.albedo = std::move(texture);


        render_state.push_back(DrawCall(&square));
        render_state.push_back(DrawCall(&cube));
        render_state.push_back(DrawCall(&triangleTest));
        render_state.push_back(DrawCall(&text,&textShaderProgram));

        
        for (auto &&i : render_state)
        {
            i.material = &material;
            forwardGeometry->pushDrawCall(&i);
        }
        // render loop
        // -----------
        while (!glfwWindowShouldClose(window))
        {
            // input
            // -----
            processInput(window);

            renderer->clear();

            double xpos, ypos;
            glfwGetCursorPos(window,&xpos, &ypos);
            ypos = abs(ypos - SCR_HEIGHT); 
            triangleTest.setPosition(glm::vec3(xpos, ypos,-1));
            glm::vec3 rot = triangleTest.getRotation();
            rot.z += 0.005f;
            triangleTest.setRotation(rot);
            rot = cube.getRotation();
            rot.x += 0.002f;
            rot.y += 0.003f;
            cube.setRotation(rot);


            renderer->renderFrame();
            for (auto &&i : render_state)
            {
                forwardGeometry->pushDrawCall(&i);
            }
            


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

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window,GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        std::cout << "capture" << std::endl;
        renderer->captureScreenshot("./test.png",GL_RGBA);
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