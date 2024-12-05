#pragma once

#include <string>
#include "bezier.h"

class MotionPath
{
private:
    std::string filename_;
    std::vector<Bezier> beziers_;
    bool reverse_;

public:
    MotionPath(std::string filename);
    void SetReversed(bool reverse);
    void Init();
    Vect GetPositionForTime(float t);
};