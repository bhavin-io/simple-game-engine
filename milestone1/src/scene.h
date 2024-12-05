#pragma once
#include <vector>
#include <string>

#include "entity.h"
#include "point_light.h"
#include "camera.h"
#include "shader_program.h"

class Scene
{
private:
    std::string envfile_;
    std::string lightfile_;
    std::string bezierfile_;
    Entity *environment_;
    std::vector<Entity *> entities_;
    std::vector<PointLight *> lights_;
    Camera *camera_;
    ShaderProgram *shader_program_;
    int num_lights_;

    void LoadLightsFromFile();
    void SetupCameraWithMotionPath();
    void SetupEnvironmentFromFile();

public:
    Scene(std::string envfile,
          std::string lightfile,
          std::string bezierfile);
    bool Init();
    void SceneDraw(float t);
};
