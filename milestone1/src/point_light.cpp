#include "point_light.h"
#include "vect/vect.h"

PointLight::PointLight(int id, Vect pos)
    : id_(id),
      pos_(pos)
{
}

Vect PointLight::GetPosition()
{
    return pos_;
}
