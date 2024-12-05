#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <GL/glew.h>  // Include OpenGL types

// Define Vertex Information
struct VertexInfo {
    float x, y, z;           // Vertex coordinates
    float normal_x, normal_y, normal_z; // Normal coordinates
    float u, v;              // Texture coordinates

    // Constructor with initialization
    VertexInfo(float px = 0.0f, float py = 0.0f, float pz = 0.0f, 
               float nx = 0.0f, float ny = 0.0f, float nz = 0.0f, 
               float tu = 0.0f, float tv = 0.0f)
        : x(px), y(py), z(pz), normal_x(nx), normal_y(ny), normal_z(nz), u(tu), v(tv) {}
};

// Define Triangle using VertexInfo
struct Triangle {
    VertexInfo v1, v2, v3;

    Triangle( VertexInfo& vertex1,  VertexInfo& vertex2,  VertexInfo& vertex3)
        : v1(vertex1), v2(vertex2), v3(vertex3) {}
};

class Model {
public:
    std::vector<VertexInfo> normals;          // Separate vector for normals
    std::vector<VertexInfo> textureCoords;    // Separate vector for texture coordinates
    std::vector<VertexInfo> vertices;
    std::vector<unsigned int> indices;  // Store indices for indexed drawing

    Model();
    ~Model();

    void addVertex(float x, float y, float z, float nx = 0.0f, float ny = 0.0f, float nz = 0.0f, float u = 0.0f, float v = 0.0f);
    void addFace(unsigned int v1, unsigned int v2, unsigned int v3,
    unsigned int n1, unsigned int n2, unsigned int n3,
    unsigned int t1, unsigned int t2, unsigned int t3);
  // Method declarations
    void addNormal(float nx, float ny, float nz);
    void addTextureCoordinate(float u, float v);
    std::vector<Triangle> getAllTriangles() ;
    int getNumTriangles() ;
};
