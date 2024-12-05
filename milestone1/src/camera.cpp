#include "camera.h"
#include <iostream>
#include "shader_program.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 GetViewMatrix(Vect eye, Vect gaze, Vect up) {
    gaze = gaze.normalize();
    Vect w = -gaze; // gaze is already normalized
    Vect u = (up.cross(w)).normalize();
    Vect v = w.cross(u);

    glm::mat4 move = glm::mat4(1, 0, 0, 0,
                               0, 1, 0, 0,
                               0, 0, 1, 0,
                               -eye.x, -eye.y, -eye.z, 1);

    glm::mat4 rot = glm::mat4(u.x, v.x, w.x, 0,
                              u.y, v.y, w.y, 0,
                              u.z, v.z, w.z, 0,
                              0, 0, 0, 1);

    glm::mat4 view = rot * move;
    return view;
}

Camera::Camera(MotionPath *path, Vect up) : path_(path), up_(up) {
}

Camera::Camera(Vect eye, Vect look_at, Vect up) : 
path_(nullptr), eye_(eye), up_(up) {
    gaze_ =(look_at - eye).normalize();
}

void Camera::CameraDraw(float t, ShaderProgram* shader_program) {
    if (path_ != nullptr) {
        Vect previous_eye = eye_;
        eye_ = path_->GetPositionForTime(t);
        Vect next_eye = path_->GetPositionForTime(t + 0.001);

        if (next_eye != eye_) {
            gaze_ = (next_eye - eye_).normalize();
        } else {
            gaze_ = (eye_ - previous_eye).normalize();
        }
    }

    glm::mat4 view = GetViewMatrix(eye_, gaze_, up_);
    shader_program->SetUniformValue("view_transform", view);
}

