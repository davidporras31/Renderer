
#include "../include/UBO.h"

UBO::UBO() {
    glGenBuffers(1, &ubo);
}

UBO::~UBO() {
    glDeleteBuffers(1, &ubo);
}

void UBO::bindData(const void *data, size_t size)
{
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

void UBO::bindToBindingPoint(int const bindingPoint) const
{
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, ubo);
}
