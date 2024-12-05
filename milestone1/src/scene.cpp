#include "scene.h"
#include <iostream>
#include <fstream>
#include "basic_shader.h"
#include "point_light.h"

Scene::Scene(
    std::string envfile,
    std::string lightfile,
    std::string bezierfile) : 
    envfile_(envfile),
    lightfile_(lightfile),
    bezierfile_(bezierfile) {}

void Scene::LoadLightsFromFile()
{
    std::cout << "Scene: loading lights from " << lightfile_ << std::endl;

    std::ifstream infile;
    infile.open(lightfile_);

    if (!infile.is_open())
    {
        std::cout << "Scene: could not find file " << lightfile_ << std::endl;
        throw 1;
    }

    float x, y, z;
    num_lights_ = 0;

    while (infile >> x >> y >> z)
    {
        std::cout << "Scene: found light" << std::endl;
        PointLight *light = new PointLight(num_lights_, Vect(x, y, z));
        lights_.push_back(light);
        num_lights_++;

        if (num_lights_ >= 20)
        {
            std::cout << "Scene: warning, maximum number of lights (20) reached." << std::endl;
            break;
        }
    }

    infile.close();
}

void Scene::SetupCameraWithMotionPath() {
    std::cout << "Scene: loading motion path from " << bezierfile_ << std::endl;
    MotionPath* path = new MotionPath(bezierfile_);
    path->Init();
    path->SetReversed(true);
    camera_ = new Camera(path, Vect(0, 0, 1));
}

void Scene::SetupEnvironmentFromFile() {
    std::cout << "Scene: setting up environment from " << envfile_ << std::endl;
    environment_ = new Entity();
    environment_->LoadMeshFromFile(envfile_);
}

bool Scene::Init() {
    std::cout << "Scene: initializing" << std::endl;

        LoadLightsFromFile();
        SetupCameraWithMotionPath();
        SetupEnvironmentFromFile();
    

    if ( !environment_->Init()) {
        std::cout << "Scene: failed to initialize environment" << std::endl;
        return false;
    }

    std::cout << "Scene: setting up shader program" << std::endl;
    shader_program_ = new BasicShader();
    if ( !shader_program_->Init()) {
        std::cerr << "Scene: failed to initialize shader program" << std::endl;
        return false;
    }

    std::cout << "Scene: finished setting up scene." << std::endl;
    return true;
}

void Scene::SceneDraw(float t) {
    
    shader_program_->SelectForDrawing();
    std::vector<Vect> light_positions;
    for (int i = 0; i < lights_.size(); i++) {
        light_positions.push_back(lights_[i]->GetPosition());
    }

    shader_program_->SetUniformValue("num_lights", static_cast<int>(lights_.size()));
    shader_program_->SetUniformValue("lights", light_positions);

   
        camera_->CameraDraw(t, shader_program_);
    

        environment_->EntityDraw(shader_program_);
    

    for (auto entity : entities_) {
        entity->EntityDraw(shader_program_);
    }
}
