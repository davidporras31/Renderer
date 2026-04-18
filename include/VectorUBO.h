#ifndef VECTOR_UBO_H
#define VECTOR_UBO_H

#include "UBO.h"
#include "Test.hpp"
#include <type_traits>
/// @brief A wrapper around a UBO that manages a UBO for sending the vector data to the GPU. a alignment of 16 bytes is assumed for the vector elements.
/// @tparam T The type of the elements in the vector. Must be trivially copyable and have a size that is a multiple of 16 bytes.
template <typename T, size_t S, typename TS = int>
class VectorUBO
{
private:
    UBO ubo;
    struct alignas(16) VectorUBOData
    {
        int size;
        float _pad[3]; // padding to align to 16 bytes
        T data[S];
    };
    VectorUBOData data;

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
};

template <typename T, size_t S, typename TS>
inline VectorUBO<T, S, TS>::VectorUBO()
{
    static_assert(sizeof(VectorUBOData) % 16 == 0, "Size of VectorUBOData must be a multiple of 16 bytes");
    static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");
    static_assert(sizeof(T) % 16 == 0, "Size of T must be a multiple of 16 bytes");
    data.size = 0;
}

template <typename T, size_t S, typename TS>
inline VectorUBO<T, S, TS>::~VectorUBO()
{
}

template <typename T, size_t S, typename TS>
inline UBO &VectorUBO<T, S, TS>::getUBO()
{
    return ubo;
}

template <typename T, size_t S, typename TS>
inline void VectorUBO<T, S, TS>::bindData()
{
    ubo.bindData(&data, sizeof(VectorUBOData));
}

template <typename T, size_t S, typename TS>
inline void VectorUBO<T, S, TS>::bindToBindingPoint(int const bindingPoint) const
{
    ubo.bindToBindingPoint(bindingPoint);
}

template <typename T, size_t S, typename TS>
inline void VectorUBO<T, S, TS>::pushBack(const T &element)
{
    data.data[static_cast<size_t>(data.size)] = element;
    data.size++;
}

template <typename T, size_t S, typename TS>
inline size_t VectorUBO<T, S, TS>::getSize() const
{
    return data.size; // return the size of the vector in number of elements
}

template <typename T, size_t S, typename TS>
inline const T &VectorUBO<T, S, TS>::operator[](size_t index) const
{
    return data.data[static_cast<size_t>(index)];
}

template <typename T, size_t S, typename TS>
inline void VectorUBO<T, S, TS>::clear()
{
    data.size = 0;
}

#endif // VECTOR_UBO_H