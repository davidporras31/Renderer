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
class VectorUBO : public Vector<T, TS>
{
private:
    UBO ubo;
public:
    VectorUBO();
    ~VectorUBO();
    UBO &getUBO();

    void bindData();
    void bindToBindingPoint(int const bindingPoint) const;

    /// @brief Push a new element to the back of the vector but grow is disabled. If the vector is full, an exception will be thrown.
    /// @param element The element to push.
    /// @throws std::runtime_error if the vector is full.
    void pushBack(const T &element);
};

template <typename T, typename TS>
inline VectorUBO<T, TS>::VectorUBO()
{
    static_assert(sizeof(T) % 16 == 0, "Size of T must be a multiple of 16 bytes");
    static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");
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
    ubo.bindData(Vector<T, TS>::getData(), Vector<T, TS>::getCapacity() * sizeof(T));
}

template <typename T, typename TS>
inline void VectorUBO<T, TS>::bindToBindingPoint(int const bindingPoint) const
{
    ubo.bindToBindingPoint(bindingPoint);
}

template <typename T, typename TS>
inline void VectorUBO<T, TS>::pushBack(const T &element)
{
    if(Vector<T, TS>::getSize() >= Vector<T, TS>::getCapacity())
    {
        throw std::runtime_error("VectorUBO: Exceeded maximum size");
    }
    Vector<T, TS>::pushBack(element);
}

#endif // VECTOR_UBO_H