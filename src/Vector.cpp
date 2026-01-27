#include "../include/Vector.h"

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
    #ifdef TESTMODE //just to remove unused variable warning
    size_t oldCapacity = vec.getCapacity();
    #endif  // TESTMODE
    vec.safeClear();
    REC_EQL(vec.getSize(), 0);
    REC_LEQL(vec.getCapacity(), oldCapacity);
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
TEST("Vector", "safePopBack functionality")
{
    Vector<int> vec;
    for (int i = 0; i < 50; ++i)
    {
        vec.pushBack(i);
    }
    REC_EQL(vec.getSize(), 50);
    vec.safePopBack();
    REC_EQL(vec.getSize(), 49);
}
TEST("Vector", "safePopBack with non-trivially destructible type")
{
    Vector<std::string> vec;
    vec.pushBack("Hello");
    vec.pushBack("World");
    REC_EQL(vec.getSize(), 2);
    vec.safePopBack();
    REC_EQL(vec.getSize(), 1);
}
TEST("Vector", "safeClear with non-trivially destructible type")
{
    Vector<std::string> vec;
    vec.pushBack("Hello");
    vec.pushBack("World");
    REC_EQL(vec.getSize(), 2);
    vec.safeClear();
    REC_EQL(vec.getSize(), 0);
}
TEST("Vector", "emplaceBack functionality")
{
    Vector<std::string> vec;
    vec.emplaceBack("Hello");
    vec.emplaceBack("World");
    REC_EQL(vec.getSize(), 2);
    REC_EQL(vec[0], "Hello");
    REC_EQL(vec[1], "World");
}
TEST("Vector", "getData functionality")
{
    Vector<int> vec;
    for (int i = 0; i < 10; ++i)
    {
        vec.pushBack(i);
    }
    REC_EQL(vec.getSize(), 10);
    #ifdef TESTMODE //just to remove unused variable warning
    int *data = vec.getData();
    for (int i = 0; i < 10; ++i)
    {
        REC_EQL(data[i], i);
    }
    #endif  // TESTMODE
}