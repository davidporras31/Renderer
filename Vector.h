#ifndef VECTOR_H
#define VECTOR_H

#include <cstring>
#include <utility>

#ifndef VECTOR_BASE_CAPACITY
#define VECTOR_BASE_CAPACITY 8
#endif
#ifndef VECTOR_GROW_FACTOR
#define VECTOR_GROW_FACTOR capacity * 3/4
#endif

template <typename T, typename S = size_t>
class Vector
{
private:
    T *data;
    S capacity;
    S size;
    void expand();

public:
    Vector();
    ~Vector();

    void pushBack(const T& val);
    void pushBack(T&& val);
    void popBack();

    void clear();
    void safeClear();

    T& operator[](S i) const;
    S getSize() const;
};

template <typename T, typename S>
inline void Vector<T, S>::expand()
{
    capacity += VECTOR_GROW_FACTOR;
    T *tmp = new T[capacity];
    memcpy(tmp, data, size * sizeof(T));
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
inline void Vector<T, S>::clear()
{
    size = 0;
}

template <typename T, typename S>
inline void Vector<T, S>::safeClear()
{
    delete[] data;
    data = new T[VECTOR_BASE_CAPACITY];
    capacity = VECTOR_BASE_CAPACITY;
    size = 0;
}

template <typename T, typename S>
inline T &Vector<T, S>::operator[](S i) const
{
    return data[i];
}

template <typename T, typename S>
inline S Vector<T, S>::getSize() const
{
    return size;
}
#endif // VECTOR_H