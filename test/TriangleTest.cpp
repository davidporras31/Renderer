#include "TriangleTest.h"

TriangleTest::TriangleTest()
{
    float vertices[] = {
        // positions
         0.0f,  0.5f, 0.0f,     0.5f,0.0f,
        -0.5f, -0.5f, 0.0f,     0.0f,1.0f,
         0.5f, -0.5f, 0.0f,     1.0f,1.0f
    };
    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 
    glDeleteBuffers(1, &VBO);
}

TriangleTest::~TriangleTest()
{
    glDeleteVertexArrays(1, &VAO);
}

void TriangleTest::draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
