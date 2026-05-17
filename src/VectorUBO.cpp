#include "../include/VectorUBO.h"

TEST("VectorUBO", "Test memory allocation and deallocation")
{
    struct VectorUBOTestData
    {
        float a;
        float padding[3]; // padding to ensure that the size of the struct is a multiple of 16 bytes
    };

    VectorUBO<VectorUBOTestData> vectorUBO;
    REC_EQL(vectorUBO.getSize(), 0); // Check that the size is initially 0
}

TEST("VectorUBO", "Test storage and retrieval of data in the VectorUBO class")
{
    struct VectorUBOTestData
    {
        float a;
        float padding[3]; // padding to ensure that the size of the struct is a multiple of 16 bytes
    };

    VectorUBO<VectorUBOTestData> vectorUBO;
    vectorUBO.pushBack(VectorUBOTestData{1.f, {0.f, 0.f, 0.f}});
    vectorUBO.pushBack(VectorUBOTestData{2.f, {0.f, 0.f, 0.f}});
    vectorUBO.pushBack(VectorUBOTestData{3.f, {0.f, 0.f, 0.f}});
    vectorUBO.pushBack(VectorUBOTestData{4.f, {0.f, 0.f, 0.f}});

    // Check that the size is correct
    REC_EQL(vectorUBO.getSize(), 4);

    // Check that the data is correct
    REC_EQL(vectorUBO[0].a, 1.f);
    REC_EQL(vectorUBO[1].a, 2.f);
    REC_EQL(vectorUBO[2].a, 3.f);
    REC_EQL(vectorUBO[3].a, 4.f);
}

TEST("VectorUBO", "Test storage and retrieval of huge data in the VectorUBO class")
{
    VectorUBO<long double> vectorUBO;
    for (long double i = 0; i < 1000; ++i)
    {
        vectorUBO.pushBack(i);
    }

    // Check that the size is correct
    REC_EQL(vectorUBO.getSize(), 1000);

    // Check that the data is correct
    for (long double i = 0; i < 1000; ++i)
    {
        REC_EQL(vectorUBO[i], i);
    }
}

TEST("VectorUBO", "Test storage and retrieval of huge data bigger then float in the VectorUBO class")
{
    struct alignas(16) Foo
    {
        float a;
        float b;
        float c;
        float d;
    };

    VectorUBO<Foo> vectorUBO;
    for (float i = 0; i < 1000; ++i)
    {
        vectorUBO.pushBack(Foo{i, i + (1 << 16)});
    }

    // Check that the size is correct
    REC_EQL(vectorUBO.getSize(), 1000);

    // Check that the data is correct
    for (long double i = 0; i < 1000; ++i)
    {
        REC_EQL(vectorUBO[i].a, i);
        REC_EQL(vectorUBO[i].b, i + (1 << 16));
        REC_TRUE(vectorUBO[i].b > vectorUBO[i].a);
    }
}

TEST("VectorUBO", "Test clear function")
{
    struct VectorUBOTestData
    {
        float a;
        float padding[3]; // padding to ensure that the size of the struct is a multiple of 16 bytes
    };
    VectorUBO<VectorUBOTestData> vectorUBO;
    vectorUBO.pushBack(VectorUBOTestData{1.f, {0.f, 0.f, 0.f}});
    vectorUBO.pushBack(VectorUBOTestData{2.f, {0.f, 0.f, 0.f}});
    vectorUBO.pushBack(VectorUBOTestData{3.f, {0.f, 0.f, 0.f}});
    vectorUBO.pushBack(VectorUBOTestData{4.f, {0.f, 0.f, 0.f}});

    vectorUBO.clear(); // Clear the vector

    // Check that the size is correct
    REC_EQL(vectorUBO.getSize(), 0);
}