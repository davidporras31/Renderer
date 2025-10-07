#include "Cube.h"

Cube::Cube()
{
    float vertices[] = {
        // positions          // texture coords
        -1.0f,  -1.0f,   -1.0f,  0.0f, 0.0f,
        +1.0f,  -1.0f,   -1.0f,  1.0f, 0.0f,
        +1.0f,  +1.0f,   -1.0f,  1.0f, 1.0f,
        -1.0f,  +1.0f,   -1.0f,  0.0f, 1.0f,
        -1.0f,  -1.0f,   +1.0f,  0.0f, 0.0f,
        +1.0f,  -1.0f,   +1.0f,  1.0f, 0.0f,
        +1.0f,  +1.0f,   +1.0f,  1.0f, 1.0f,
        -1.0f,  +1.0f,   +1.0f,  0.0f, 1.0f,
    };
    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        4, 0, 3, 3, 7, 4,
        1, 5, 6, 6, 2, 1,
        4, 5, 1, 1, 0, 4,
        3, 2, 6, 6, 7, 3
    };
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);
// 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(0); 
}

Cube::~Cube()
{
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
}

void Cube::draw()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
}