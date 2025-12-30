#include "Vector.h"

TEST("Vector", "Basic functionality")
{
    Vector<int> vec;
    for (int i = 0; i < 100; ++i)
    {
        vec.pushBack(i);
    }
    REC_EQL(vec.getSize(), 100);
    for (int i = 0; i < 100; ++i)
    {
        REC_EQL(vec[i], i);
    }
}
TEST("Vector", "popBack functionality")
{
    Vector<int> vec;
    for (int i = 0; i < 50; ++i)
    {
        vec.pushBack(i);
    }
    REC_EQL(vec.getSize(), 50);
    for (int i = 0; i < 20; ++i)
    {
        vec.popBack();
    }
    REC_EQL(vec.getSize(), 30);
    for (int i = 0; i < 30; ++i)
    {
        REC_EQL(vec[i], i);
    }
}
TEST("Vector", "reserve functionality")
{
    Vector<int> vec;
    vec.reserve(200);
    REC_EQL(vec.getSize(), 0);
    for (int i = 0; i < 150; ++i)
    {
        vec.pushBack(i);
    }
    REC_EQL(vec.getSize(), 150);
    for (int i = 0; i < 150; ++i)
    {
        REC_EQL(vec[i], i);
    }
    REC_EQL(vec.getCapacity(), 200);
}
TEST("Vector", "clear and safeClear functionality")
{
    Vector<int> vec;
    for (int i = 0; i < 80; ++i)
    {
        vec.pushBack(i);
    }
    REC_EQL(vec.getSize(), 80);
    vec.clear();
    REC_EQL(vec.getSize(), 0);
    for (int i = 0; i < 60; ++i)
    {
        vec.pushBack(i);
    }
    REC_EQL(vec.getSize(), 60);
    for (int i = 0; i < 60; ++i)
    {
        REC_EQL(vec[i], i);
    }
    vec.safeClear();
    REC_EQL(vec.getSize(), 0);
    REC_LEQL(vec.getCapacity(), 16); // assuming VECTOR_BASE_CAPACITY is 16
}
TEST("Vector", "pushBack with rvalue functionality")
{
    Vector<std::string> vec;
    for (int i = 0; i < 30; ++i)
    {
        vec.pushBack("String " + std::to_string(i));
    }
    REC_EQL(vec.getSize(), 30);
    for (int i = 0; i < 30; ++i)
    {
        REC_EQL(vec[i], "String " + std::to_string(i));
    }
}
TEST("Vector", "last() functionality")
{
    Vector<int> vec;
    for (int i = 0; i < 10; ++i)
    {
        vec.pushBack(i * 10);
        REC_EQL(vec.last(), i * 10);
    }
    REC_EQL(vec.getSize(), 10);
    REC_EQL(vec.last(), 90);
}
TEST("Vector", "operator[] functionality")
{
    Vector<double> vec;
    for (int i = 0; i < 25; ++i)
    {
        vec.pushBack(i * 1.5);
    }
    REC_EQL(vec.getSize(), 25);
    for (int i = 0; i < 25; ++i)
    {
        REC_EQL(vec[i], i * 1.5);
    }
}