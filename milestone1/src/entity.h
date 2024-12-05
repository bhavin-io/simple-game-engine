#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include "loader/model.h"
#include "vect/vect.h"
#include "shader_program.h"

// Entity class
class Entity
{
private:
    std::string filename_;
    GLuint varray_name_;
    GLuint vbuffer_name_;
    int num_verts_;
    glm::mat4 model_transform_;

protected:
    Model *model_;

public:
    Entity();
    void LoadMeshFromFile(std::string filename);
    bool Init();
    void EntityDraw(ShaderProgram *shader_program);
    void ScaleBy(float n);
    void TranslateBy(Vect v);
    void RotateBy(char axis, float amount);
};
