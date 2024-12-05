#pragma once

#include "scene.h"
#include "camera.h"

class Engine
{
    private:
        Scene *scene_;

    public:
        Engine();
        void SetScene(Scene *scene);

        void Run();
};