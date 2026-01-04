#include "../include/Square.h"

Square::Square()
{
    float vertices[] = {
        // positions     // normals        // texture coords
        -1.0f,  +1.0f,   0.0f,  -1.0f,  +1.0f,   0.0f,       0.0f,1.0f,
        +1.0f,  +1.0f,   0.0f,  +1.0f,  +1.0f,   0.0f,       1.0f,1.0f,
        +1.0f,  -1.0f,   0.0f,  +1.0f,  -1.0f,   0.0f,       1.0f,0.0f,
        -1.0f,  -1.0f,   0.0f,  -1.0f,  -1.0f,   0.0f,       0.0f,0.0f,
    };
    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glGenVertexArrays(1,&VAO);

    glBindVertexArray(VAO);
// 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //glDeleteBuffers(1,&VBO);
    //glDeleteBuffers(1,&EBO);
}

Square::~Square()
{
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&EBO);
    glDeleteBuffers(1,&VBO);
}

void Square::draw(ShaderProgram* shader) 
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}