#include "obj_loader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>  // Include this for std::replace
#include <stdexcept>
#include "model.h" // Ensure the Model and VertexInfo are included correctly

Model ObjLoader::LoadObjFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        }    

    Model model;
    std::vector<VertexInfo> temp_vertices;
    std::vector<VertexInfo> temp_normals;
    std::vector<VertexInfo> temp_texCoords;

    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {  // Vertex position
            float x, y, z;
            iss >> x >> y >> z;
            std::cout << "Vertex: " << x << ", " << y << ", " << z << std::endl;
            temp_vertices.emplace_back(x, y, z);
        } else if (prefix == "vt") {  // Texture coordinate
            float u, v;
            iss >> u >> v;
            std::cout << "Texture: " << u << ", " << v << std::endl;
            temp_texCoords.emplace_back(u, v, 0);
        } else if (prefix == "vn") {  // Vertex normal
            float nx, ny, nz;
            iss >> nx >> ny >> nz;
            std::cout << "Normal: " << nx << ", " << ny << ", " << nz << std::endl;
            temp_normals.emplace_back(nx, ny, nz);
        } else if (prefix == "f") {  // Faces
            std::string vertexData;
            for (int i = 0; i < 3; i++) {
                iss >> vertexData;
                std::replace(vertexData.begin(), vertexData.end(), '/', ' ');
                std::istringstream vertexStream(vertexData);
                
                int vertexIndex, texCoordIndex = -1, normalIndex = -1;
                vertexStream >> vertexIndex >> texCoordIndex >> normalIndex;
                
                VertexInfo vertex;
                vertex.x = temp_vertices[vertexIndex - 1].x;
                vertex.y = temp_vertices[vertexIndex - 1].y;
                vertex.z = temp_vertices[vertexIndex - 1].z;
                
                if (texCoordIndex != -1) {
                    vertex.u = temp_texCoords[texCoordIndex - 1].x;
                    vertex.v = temp_texCoords[texCoordIndex - 1].y;
                }
                
                if (normalIndex != -1) {
                    vertex.normal_x = temp_normals[normalIndex - 1].x;
                    vertex.normal_y = temp_normals[normalIndex - 1].y;
                    vertex.normal_z = temp_normals[normalIndex - 1].z;
                }
                std ::cout << "Face: " << vertex.x << ", " << vertex.y << ", " << vertex.z << std::endl;
                model.vertices.push_back(vertex);
                model.indices.push_back(static_cast<unsigned int>(model.vertices.size() - 1));
            }
        }
    }

    return model;
}
