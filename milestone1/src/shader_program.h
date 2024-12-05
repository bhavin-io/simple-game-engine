#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "vect/vect.h"
#include <string>
#include <unordered_map>
#include <vector>

class ShaderProgram
{
private:
    GLuint GetUniformLocation(std::string name);

protected:
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint shader_program;
    std::unordered_map<std::string, GLuint> uniform_locations;

    std::string shader_program_name;
    bool InitVertexShader();
    bool InitFragmentShader();

public:
    virtual std::string GetFragmentShaderCode() = 0;
    virtual std::string GetVertexShaderCode() = 0;
    bool Init();
    void SetUniformValue(std::string name, float value);
    void SetUniformValue(std::string name, Vect value);
    void SetUniformValue(std::string name, std::vector<Vect> values);
    void SetUniformValue(std::string name, int value);
    void SetUniformValue(std::string name, glm::mat4 value);
    void SelectForDrawing();
};
