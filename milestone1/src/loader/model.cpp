#include "model.h"
#include "obj_loader.h"
#include <iostream>  // This includes std::cout, std::cin, and std::endl
  // Ensure this loader is compatible with your VertexInfo structure

Model::Model() {
    // Initialize any necessary members, if applicable
}

Model::~Model() {
    // Clean up resources, if any were allocated
}




void Model::addVertex(float x, float y, float z, float nx, float ny, float nz, float u, float v) {
    vertices.emplace_back(x, y, z, nx, ny, nz, u, v);
}

void Model::addFace(unsigned int v1, unsigned int v2, unsigned int v3,
    unsigned int n1, unsigned int n2, unsigned int n3,
    unsigned int t1, unsigned int t2, unsigned int t3) {
    indices.push_back(v1);  
    indices.push_back(v2);
    indices.push_back(v3);
}

void Model::addNormal(float nx, float ny, float nz) {
    normals.emplace_back(nx, ny, nz);
}

void Model::addTextureCoordinate(float u, float v) {
    textureCoords.emplace_back(u, v, 0); // Assuming Vect can handle 2D textures with an unused z-component
}

std::vector<Triangle> Model::getAllTriangles() {
    std::vector<Triangle> triangles;
    if (indices.size() % 3 != 0) {
        throw std::runtime_error("Indices count is not a multiple of 3.");
    }
    for (size_t i = 0; i < indices.size(); i += 3) {
        triangles.emplace_back(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]]);
    }
    return triangles;
}

int Model::getNumTriangles() {
    return static_cast<int>(indices.size()) / 3; // Assumes that each face is a triangle
}
