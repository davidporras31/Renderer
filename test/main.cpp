#include <iostream>
#include "../Renderer.h"
#include <GLFW/glfw3.h>
#include "TriangleTest.h"
#include "../OrthographicCamera.h"
#include "../ShaderProgram.h"

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

        TriangleTest triangleTest;
        triangleTest.setPosition({0.5f,0.5f,-1.f});
        triangleTest.setScale({SCR_WIDTH/2,SCR_HEIGHT/2,1.f});
        OrthographicCamera camera(0.f, SCR_WIDTH, 0.f, SCR_HEIGHT, 0.1f, 100.0f);
        camera.setPosition({0,0,-2});

        ShaderProgram shaderProgram("basic_shader",
            {
                {"test/triangle.vs", GL_VERTEX_SHADER},
                {"test/triangle.fs", GL_FRAGMENT_SHADER}
            },
            "bin");

            
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

            shaderProgram.use();
            shaderProgram.setMat4("projection", camera.getProjection());
            shaderProgram.setMat4("view", camera.getTransform());
            shaderProgram.setMat4("model", triangleTest.getTransform());
            triangleTest.draw();

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
        renderer->captureScreenshot("test.png");
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    
    renderer->setViewport({0, 0, width, height});
}