#ifndef VECTOR_UBO_H
#define VECTOR_UBO_H

#include "Vector.h"
#include "UBO.h"
#include "Test.hpp"
#include <type_traits>
#include <glm/glm.hpp>
/// @brief A wrapper around a UBO that manages a UBO for sending the vector data to the GPU. a alignment of 16 bytes is assumed for the vector elements.
/// @tparam T The type of the elements in the vector. Must be trivially copyable and have a size that is a multiple of 16 bytes.
template <typename T, typename TS = size_t>
class VectorUBO
{
private:
    UBO ubo;
    // The data stored in the UBO. The first element is the size of the vector followed by the elements of the vector. The size of the vector is stored as a vec4 to ensure that it is a multiple of 16 bytes.
    Vector<glm::vec4, TS> data;
    TS maxSize = 0;
public:
    VectorUBO();
    ~VectorUBO();
    UBO &getUBO();

    void bindData();
    void bindToBindingPoint(int const bindingPoint) const;

    void pushBack(const T &element);
    size_t getSize() const;
    const T &operator[](size_t index) const;
    void clear();
    TS getMaxSize() const { return maxSize; }
    void setMaxSize(TS newMaxSize);
};

template <typename T, typename TS>
inline VectorUBO<T, TS>::VectorUBO()
{
    static_assert(sizeof(T) % 16 == 0, "Size of T must be a multiple of 16 bytes");
    static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");
    data.pushBack(glm::vec4(0.0f)); // Initialize the first element to store the size of the vector, which is initially 0
}

template <typename T, typename TS>
inline VectorUBO<T, TS>::~VectorUBO()
{
}

template <typename T, typename TS>
inline UBO &VectorUBO<T, TS>::getUBO()
{
    return ubo;
}

template <typename T, typename TS>
inline void VectorUBO<T, TS>::bindData()
{
    ubo.bindData(&data, sizeof(glm::vec4) * maxSize * (sizeof(T) / sizeof(glm::vec4)));
}

template <typename T, typename TS>
inline void VectorUBO<T, TS>::bindToBindingPoint(int const bindingPoint) const
{
    ubo.bindToBindingPoint(bindingPoint);
}

template <typename T, typename TS>
inline void VectorUBO<T, TS>::pushBack(const T &element)
{
    if(data[0].x >= maxSize)
    {
        throw std::runtime_error("VectorUBO: Exceeded maximum size");
    }
    size_t typeSizeinVec4 = sizeof(T) / sizeof(glm::vec4);
    for (size_t i = 0; i < typeSizeinVec4; ++i)
    {
        data.pushBack(glm::vec4()); // create empty space for the new element.
    }
    *reinterpret_cast<T *>(&data[data.getSize() - typeSizeinVec4]) = element;
    data[0].x = static_cast<float>((data.getSize() - 1) / typeSizeinVec4); // Update the size of the vector, which is stored in the first element
}

template <typename T, typename TS>
inline size_t VectorUBO<T, TS>::getSize() const
{
    size_t typeSizeinVec4 = sizeof(T) / sizeof(glm::vec4);
    return (data.getSize() - 1) / typeSizeinVec4;
}

template <typename T, typename TS>
inline const T &VectorUBO<T, TS>::operator[](size_t index) const
{
    size_t typeSizeinVec4 = sizeof(T) / sizeof(glm::vec4);
    return *reinterpret_cast<const T *>(&data[index * typeSizeinVec4 + 1]);
}

template <typename T, typename TS>
inline void VectorUBO<T, TS>::clear()
{
    data.clear();
    data.pushBack(glm::vec4(0.0f)); // Reset the first element to store the size of the vector, which is now 0
}

template <typename T, typename TS>
inline void VectorUBO<T, TS>::setMaxSize(TS newMaxSize)
{
    maxSize = newMaxSize;
    data.reserve(1 + (maxSize * sizeof(T) / sizeof(glm::vec4))); // Reserve enough space for the size element and the maximum number of elements
}

#endif // VECTOR_UBO_H