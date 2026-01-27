#ifndef VECTOR_H
#define VECTOR_H

#include <cstring>
#include <utility>
#include <assert.h>
#include "Test.hpp"

#ifndef VECTOR_BASE_CAPACITY
#define VECTOR_BASE_CAPACITY 8
#endif
#ifndef VECTOR_GROW_FACTOR
#define VECTOR_GROW_FACTOR capacity * 3 / 4
#endif

#define VECTOR_SLIM_TYPE unsigned long
#define VECTOR_HEAVY_TYPE unsigned long long

template <typename T, typename S = size_t>
class Vector
{
private:
    T *data;
    S capacity;
    S size;
    void expand();
    void growTo(const S newSize);

public:
    Vector();
    ~Vector();

    /// @brief Adds an element to the end of the vector.
    void pushBack(const T &val);
    /// @brief Adds an element to the end of the vector.
    void pushBack(T &&val);
    /// @brief Removes the last element without calling its destructor.
    void popBack();
    /// @brief Removes the last element and calls its destructor.
    void safePopBack();

    /// @brief Constructs an element in-place at the end of the vector.
    /// @tparam Args Types of the arguments to forward to the constructor of T.
    template <typename... Args>
    void emplaceBack(Args &&...args);

    /// @brief Reserves memory for at least newCapacity elements.
    /// @param newCapacity The new capacity to reserve.
    void reserve(const S newCapacity);
    /// @brief Resizes the vector to newSize. Does not call constructors or destructors.
    /// @param newSize The new size of the vector.
    void resize(const S newSize);
    /// @brief Clears the vector without calling destructors.
    void clear();
    /// @brief Clears the vector and calls destructors.
    void safeClear();

    T &operator[](S i) const;
    T &last() const;
    
    S getSize() const;
    S getCapacity() const;
    T *getData() const;
};

template <typename T, typename S>
inline void Vector<T, S>::expand()
{
    growTo(capacity + VECTOR_GROW_FACTOR);
}

template <typename T, typename S>
inline void Vector<T, S>::growTo(S newSize)
{
    capacity = newSize;
    T *tmp = new T[capacity];
    if constexpr (std::is_trivially_copyable<T>::value)
    {
        std::memcpy(tmp, data, sizeof(T) * size);
    }
    else
    {
        for (S i = 0; i < size; ++i)
        {
            tmp[i] = std::move(data[i]);
        }
    }

    delete[] data;
    data = tmp;
}

template <typename T, typename S>
inline Vector<T, S>::Vector()
    : data(new T[VECTOR_BASE_CAPACITY]), capacity(VECTOR_BASE_CAPACITY), size(0)
{
}

template <typename T, typename S>
inline Vector<T, S>::~Vector()
{
    delete[] data;
}

template <typename T, typename S>
inline void Vector<T, S>::pushBack(const T &val)
{
    if (size >= capacity)
        expand();
    data[size++] = val;
}

template <typename T, typename S>
inline void Vector<T, S>::pushBack(T &&val)
{
    if (size >= capacity)
        expand();
    data[size++] = std::move(val);
}

template <typename T, typename S>
inline void Vector<T, S>::popBack()
{
    if (size != 0)
        --size;
}

template <typename T, typename S>
inline void Vector<T, S>::safePopBack()
{
    if (size != 0)
    {
        std::destroy_at(std::addressof(data[--size]));
    }
}

template <typename T, typename S>
inline void Vector<T, S>::reserve(S newCapacity)
{
    if (newCapacity > capacity)
    {
        growTo(newCapacity);
    }
}

template <typename T, typename S>
inline void Vector<T, S>::resize(const S newSize)
{
    resize(newSize);
    size = newSize;
}

template <typename T, typename S>
inline void Vector<T, S>::clear()
{
    size = 0;
}

template <typename T, typename S>
inline void Vector<T, S>::safeClear()
{
    auto first = std::addressof(data[0]);
    auto last = std::addressof(data[capacity - 1]);
    std::destroy(first, last + 1);
    size = 0;
}

template <typename T, typename S>
inline T &Vector<T, S>::operator[](S i) const
{
    return data[i];
}

template <typename T, typename S>
inline T &Vector<T, S>::last() const
{
    return data[size - 1];
}

template <typename T, typename S>
inline S Vector<T, S>::getSize() const
{
    return size;
}

template <typename T, typename S>
inline S Vector<T, S>::getCapacity() const
{
    return capacity;
}

template <typename T, typename S>
inline T *Vector<T, S>::getData() const
{
    return data;
}

template <typename T, typename S>
template <typename... Args>
inline void Vector<T, S>::emplaceBack(Args &&...args)
{
    if (size >= capacity)
        expand();
    new (&data[size++]) T(std::forward<Args>(args)...);
}

#endif // VECTOR_H