#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vect/vect.h"
#include <string>
#include <unordered_map>
#include "shader_program.h"
#include "shader_code/frag_glsl.h"
#include "shader_code/vert_glsl.h"

class BasicShader : public ShaderProgram
{
public:
    virtual std::string GetFragmentShaderCode()
    {
        return FRAGMENT_SHADER;
    }
    
    virtual std::string GetVertexShaderCode()
    {
        return VERTEX_SHADER;
    }
};
