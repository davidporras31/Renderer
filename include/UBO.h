
#ifndef UBO_H
#define UBO_H

#include <glad/gl.h>
#include <cstddef>

class UBO {
private:
    GLuint ubo;
public:
    UBO();
    ~UBO();

    void bindData(const void* data, size_t size);
    void bindToBindingPoint(int const bindingPoint) const;
};

#endif // UBO_H
    