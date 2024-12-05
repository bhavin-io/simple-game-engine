#pragma once

#include "motion_path.h"
#include "vect/vect.h"
#include "shader_program.h"

class Camera
{
private:
    MotionPath *path_;
    Vect eye_;
    Vect gaze_;
    Vect up_;

public:
    Camera(MotionPath *path, Vect up);
    Camera(Vect eye, Vect look_at, Vect up);
    void CameraDraw(float t, ShaderProgram *shader_program);
};
