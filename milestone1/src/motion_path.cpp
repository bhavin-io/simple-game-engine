#include "motion_path.h"
#include <string>
#include <fstream>
#include <iostream>

MotionPath::MotionPath(std::string filename)
    : filename_(filename), reverse_(false) {}

void MotionPath::SetReversed(bool reverse)
{
    reverse_ = reverse;
}

Vect MotionPath::GetPositionForTime(float t)
{
    if (reverse_)
    {
        t = 1.0 - t;
    }

    // path is segmented into n equal parts
    // where n is the number of bezier segments we have
    float num_beziers = static_cast<float>(beziers_.size());
    float segment_size = 1.0 / num_beziers;
    float segments = t / segment_size;
    int segment_num = static_cast<int>(segments);
    if (segment_num >= beziers_.size())
    {
        segment_num = beziers_.size() - 1;
    }
    if (segment_num < 0)
    {
        segment_num = 0;
    }

    Bezier b = beziers_[segment_num];
    float bezier_position = (t - static_cast<float>(segment_num) * segment_size) / segment_size;
    return b.FindPoint(bezier_position);
}

void MotionPath::Init()
{
    std::cout << "Loading Bezier curves." << std::endl;

    std::ifstream infile;
    infile.open(filename_);

    char p0type, c0type, c1type, p1type;
    float p0x, p0y, p0z;
    float c0x, c0y, c0z;
    float c1x, c1y, c1z;
    float p1x, p1y, p1z;
    int counter = 0;

    while (infile >> p0type >> p0x >> p0y >> p0z 
                  >> c0type >> c0x >> c0y >> c0z 
                  >> c1type >> c1x >> c1y >> c1z 
                  >> p1type >> p1x >> p1y >> p1z)
    {
        if (p0type != 'p' || p1type != 'p' || c0type != 'c' || c1type != 'c')
        {
            std::cout << "invalid file" << std::endl;
            throw 1;
        }

        Vect p0 = {p0x, p0y, p0z};
        Vect c0 = {c0x, c0y, c0z};
        Vect c1 = {c1x, c1y, c1z};
        Vect p1 = {p1x, p1y, p1z};

        Bezier b = {p0, c0, c1, p1};
        beziers_.push_back(b);
    }
}
