#pragma once
#include "entity.h"
#include "vect/vect.h"
#include <string>

class TestEntity : public Entity
{
private:
    void DoTri(int facenum, Vect vert0, Vect vert1, Vect vert2, Vect normal, Vect texcoordinate);

public:
    TestEntity(std::string type);
    void TriangleTest();
    void CubeTest();
};