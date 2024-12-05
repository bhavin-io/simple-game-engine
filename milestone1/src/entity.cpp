#include "entity.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "loader/obj_loader.h"
#include "shader_program.h"
Entity::Entity() { 
    model_transform_ = glm::mat4(1); 
}

void Entity::ScaleBy(float n) {
    model_transform_ = glm::scale(model_transform_, glm::vec3(n, n, n));
}

void Entity::TranslateBy(Vect v) {
    glm::vec3 translate_vec(v.x, v.y, v.z);
    model_transform_ = glm::translate(model_transform_, translate_vec);
}

void Entity::RotateBy(char axis_code, float amount) {
    glm::vec3 axis(1.0f, 0.0f, 0.0f);
    if (axis_code == 'y') {
        axis = glm::vec3(0.0f, 1.0f, 0.0f);
    } else if (axis_code == 'z') {
        axis = glm::vec3(0.0f, 0.0f, 1.0f);
    }
    model_transform_ = glm::rotate(model_transform_, amount, axis);
}

void Entity::LoadMeshFromFile(std::string filename) {
    std::cout << "Entity: loading mesh from file: " << filename << std::endl;
    filename_ = filename;
    ObjLoader loader;
    model_ = new Model(loader.LoadObjFile(filename));
}

bool Entity::Init() {
    std::cout << "Entity: initializing " << filename_ << std::endl;
    std::vector<Triangle> tris = model_->getAllTriangles();

    Triangle *triptr = &tris[0];
    VertexInfo *vinfo = reinterpret_cast<VertexInfo *>(triptr);

    num_verts_ = model_->getNumTriangles() * 3;

    glGenBuffers(1, &vbuffer_name_);
    glGenVertexArrays(1, &varray_name_);

    int stride = sizeof(VertexInfo);
    int offset1 = 3 * sizeof(GLfloat);
    int offset2 = 6 * sizeof(GLfloat);

    glBindBuffer(GL_ARRAY_BUFFER, vbuffer_name_);
    glBindVertexArray(varray_name_);

    glBufferData(GL_ARRAY_BUFFER, num_verts_ * sizeof(VertexInfo), vinfo, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(offset1));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(offset2));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

void Entity::EntityDraw(ShaderProgram *shader_program) {
    glBindVertexArray(varray_name_);
    glBindBuffer(GL_ARRAY_BUFFER, vbuffer_name_);

    shader_program->SetUniformValue("model_transform", model_transform_);

    glDrawArrays(GL_TRIANGLES, 0, num_verts_);

    GLenum error;
    // the below only works on linux
     if ((error = glGetError()) != GL_NO_ERROR)
    {
         std::cerr << "Entity: glDrawArrays produced error: " << gluErrorString(error) << std::endl;
     }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
