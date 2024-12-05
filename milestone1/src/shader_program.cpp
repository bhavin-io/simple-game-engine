#include "shader_program.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <iostream>

bool ShaderProgram::InitVertexShader()
{
    std::string vscodestr = GetVertexShaderCode();
    const GLchar *const vscode = vscodestr.c_str();

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vscode, NULL);
    glCompileShader(vertex_shader);
    GLint compileStatus;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE)
    {
        char infolog[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, infolog);
        std::cerr << "Vertex shader compilation failed" << std::endl;
        std::cerr << infolog << std::endl;
        return false;
    }
    return true;
}

bool ShaderProgram::InitFragmentShader()
{
    std::string fscodestr = GetFragmentShaderCode();
    const char *const fscode = fscodestr.c_str();

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fscode, NULL);
    glCompileShader(fragment_shader);

    GLint compileStatus;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE)
    {
        char infolog[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, infolog);
        std::cerr << "Fragment shader compilation failed" << std::endl;
        std::cerr << infolog << std::endl;
        return false;
    }
    return true;
}

bool ShaderProgram::Init()
{
    std::cout << "setting up vertex shader" << std::endl;
    if (!InitVertexShader())
    {
        return false;
    }

    std::cout << "setting up fragment shader" << std::endl;
    if (!InitFragmentShader())
    {
        return false;
    }

    std::cout << "setting up shader program" << std::endl;
    // create shader program
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    GLint status;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char infolog[512];
        glGetProgramInfoLog(shader_program, 512, NULL, infolog);
        std::cerr << "Shader program linking failed" << std::endl;
        std::cerr << infolog << std::endl;
        return false;
    }
    return true;
}

GLuint ShaderProgram::GetUniformLocation(std::string name) {
    auto it = uniform_locations.find(name);
    if (it == uniform_locations.end()) {
        GLuint uniform_loc = glGetUniformLocation(shader_program, name.c_str());
        uniform_locations[name] = uniform_loc;
        return uniform_loc;
    } else {
        return it->second;
    }
}

void ShaderProgram::SetUniformValue(std::string name, glm::mat4 matrix) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::SetUniformValue(std::string name, float value) {
    glUniform1f(GetUniformLocation(name), value);
}

void ShaderProgram::SetUniformValue(std::string name, Vect value) {
    glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void ShaderProgram::SetUniformValue(std::string name, std::vector<Vect> values) {
    GLfloat *floatVals = new GLfloat[values.size() * 3];
    for (int i = 0; i < values.size(); i++) {
        int i0 = i * 3;
        int i1 = i0 + 1;
        int i2 = i0 + 2;
        floatVals[i0] = values[i].x;
        floatVals[i1] = values[i].y;
        floatVals[i2] = values[i].z;
    }
    glUniform3fv(GetUniformLocation(name), values.size(), floatVals);
    delete[] floatVals;
}

void ShaderProgram::SetUniformValue(std::string name, int value) {
    glUniform1i(GetUniformLocation(name), value);
}

void ShaderProgram::SelectForDrawing() {
    glUseProgram(shader_program);
}
