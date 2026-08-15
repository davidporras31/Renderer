
#ifndef DEBUGPROXY_H
#define DEBUGPROXY_H

#include "../Mesh.h"

// TODO: Make new proxy meshes for each light type, with a more appropriate shape and size for each light type.
namespace DebugProxy
{
    class Directional : public Mesh
    {
    public:
        Directional();
    };

    class Point : public Mesh
    {
    public:
        Point();
    };

    class Spot : public Mesh
    {
    public:
        Spot();
    };

    class Area : public Mesh
    {
    public:
        Area();
    };
};

#endif // DEBUGPROXY_H
    