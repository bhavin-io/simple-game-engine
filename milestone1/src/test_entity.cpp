#include "test_entity.h"
#include "vect/vect.h"
#include <iostream>
#include <string>

void TestEntity::DoTri(int facenum, Vect vert0, Vect vert1, Vect vert2, Vect normal, Vect texcoordinate)
{
    int a = facenum;
    int b = facenum + 1;
    int c = facenum + 2;
    model_->addVertex(vert0.x, vert0.y, vert0.z);
    model_->addVertex(vert1.x, vert1.y, vert1.z);
    model_->addVertex(vert2.x, vert2.y, vert2.z);
    model_->addNormal(normal.x, normal.y, normal.z);
    model_->addNormal(normal.x, normal.y, normal.z);
    model_->addNormal(normal.x, normal.y, normal.z);
    model_->addTextureCoordinate(texcoordinate.x, texcoordinate.y);
    model_->addTextureCoordinate(texcoordinate.x, texcoordinate.y);
    model_->addTextureCoordinate(texcoordinate.x, texcoordinate.y);
    model_->addFace(a, a, a, b, b, b, c, c, c);
}

Vect v(int x, int y, int z)
{
    float scale = 1.0f;
    return Vect(scale * x, scale * y, scale * z);
}

Vect n(char sign, char axis)
{
    switch (axis)
    {
        case 'x':
            return sign == '+' ? Vect(1.0f, 0.0f, 0.0f) : Vect(-1.0f, 0.0f, 0.0f);
        case 'y':
            return sign == '+' ? Vect(0.0f, 1.0f, 0.0f) : Vect(0.0f, -1.0f, 0.0f);
        case 'z':
        default:
            return sign == '+' ? Vect(0.0f, 0.0f, 1.0f) : Vect(0.0f, 0.0f, -1.0f);
    }
}

Vect t()
{
    return Vect(0.0f, 1.0f);
}

TestEntity::TestEntity(std::string type)
{
    if(type == "triangle")
    {
        TriangleTest();
    }
    else
    {
        CubeTest();
    }
}

void TestEntity::TriangleTest()
{
    model_ = new Model();
    model_->addVertex(-1, -1, 0);
    model_->addVertex(0, 1, 0);
    model_->addVertex(1, -1, 0);
    model_->addNormal(0, 0, 1);
    model_->addTextureCoordinate(0, 0);
    model_->addTextureCoordinate(0, 1);
    model_->addTextureCoordinate(1, 0);
    model_->addFace(1, 1, 1, 2, 2, 2, 3, 3, 3);
}

void TestEntity::CubeTest()
{
    model_ = new Model();
    int faceOffset = 1;

    // front face
    DoTri(faceOffset,
          v(-1, -1, -1),
          v(-1, 1, -1),
          v(1, 1, -1),
          n('-', 'z'),
          t()); // t() and n() are assumed to be defined elsewhere in the code
    faceOffset += 3;
    
    DoTri(faceOffset,
          v(-1, -1, -1),
          v(1, 1, -1),
          v(1, -1, -1),
          n('-', 'z'),
          t()); // t() and n() are assumed to be defined elsewhere in the code
    faceOffset += 3;

    // right face
    DoTri(faceOffset,
          v(1, -1, -1),
          v(1, 1, -1),
          v(1, 1, 1),
          n('+', 'x'),
          t());
    faceOffset += 3;

    DoTri(faceOffset,
          v(1, -1, -1),
          v(1, 1, 1),
          v(1, -1, 1),
          n('+', 'x'),
          t());
    faceOffset += 3;

    // Top
    DoTri(faceOffset,
      v(-1, 1, -1),
      v(-1, 1, 1),
      v(1, 1, 1),
      n('+', 'y'),
      t());
    faceOffset += 3;

    DoTri(faceOffset,
      v(-1, 1, -1),
      v(1, 1, 1),
      v(1, 1, -1),
      n('+', 'y'),
      t());
    faceOffset += 3;

    // Left
    DoTri(faceOffset,
      v(-1, -1, 1),
      v(-1, 1, 1),
      v(-1, 1, -1),
      n('-', 'x'),
      t());
    faceOffset += 3;

    DoTri(faceOffset,
      v(-1, -1, 1),
      v(-1, 1, -1),
      v(-1, -1, -1),
      n('-', 'x'),
      t());
    faceOffset += 3;



    // back
    DoTri(faceOffset,
      v(1, -1, 1),
      v(1, 1, 1),
      v(-1, 1, 1),
      n('+', 'z'),
      t());
    faceOffset += 3;

    DoTri(faceOffset,
      v(1, -1, 1),
      v(-1, 1, 1),
      v(-1, -1, 1),
      n('+', 'z'),
      t());
    faceOffset += 3;

    // bottom
    DoTri(faceOffset,
      v(1, -1, -1),
      v(1, 1, -1),
      v(-1, 1, -1),
      n('-', 'y'),
      t());
    faceOffset += 3;

    DoTri(faceOffset,
      v(1, -1, -1),
      v(-1, 1, -1),
      v(-1, -1, -1),
      n('-', 'y'),
      t());
    faceOffset += 3;

}
