#pragma once

#include <vector>
#include "vect/vect.h"

class PointLight
{
private:
    Vect pos_;
    int id_;

public:
    PointLight(int id, Vect pos);
    Vect GetPosition();
};