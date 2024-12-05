#include "bezier.h"
#include <queue>
#include <vector>
#include "vect/vect.h"

Vect midpoint(Vect _p1, Vect _p2)
{
    Vect v = _p2 - _p1;
    return _p1 + (v * 0.5);
}

Bezier::Bezier(Vect p0, Vect c0, Vect c1, Vect p1)
    : p0_(p0),
      c0_(c0),
      c1_(c1),
      p1_(p1) {}

Bezier& Bezier::operator=(const Bezier &other)
{
    p0_ = other.p0_;
    c0_ = other.c0_;
    c1_ = other.c1_;
    p1_ = other.p1_;
    return *this;
}

Bezier::Bezier(const Bezier &other)
    : p0_(other.p0_),
      c0_(other.c0_),
      c1_(other.c1_),
      p1_(other.p1_) {}

Bezier::Bezier( Bezier &&other)
    : p0_(other.p0_),
      c0_(other.c0_),
      c1_(other.c1_),
      p1_(other.p1_) {}

Bezier& Bezier::operator=( Bezier &&other)
{
    p0_ = other.p0_;
    c0_ = other.c0_;
    c1_ = other.c1_;
    p1_ = other.p1_;
    return *this;
}

Vect Bezier::operator[](int i)
{
    switch (i)
    {
        case 0:
            return p0_;
        case 1:
            return c0_;
        case 2:
            return c1_;
        case 3:
            return p1_;
        default:
            return p0_;
    }
}

std::vector<Bezier> Bezier::Subdivide()
{
    // divide once
    Vect p01 = midpoint(p0_, c0_);
    Vect p12 = midpoint(c0_, c1_);
    Vect p23 = midpoint(c1_, p1_);
    // divide again
    Vect p02 = midpoint(p01, p12);
    Vect p13 = midpoint(p12, p23);
    // divide a third time
    Vect p03 = midpoint(p02, p13);

    Bezier b0 = Bezier(p0_, p01, p02, p03);
    Bezier b1 = Bezier(p03, p13, p23, p1_);

    return {b0, b1};
}

Vect Bezier::FindPoint(float u)
{
    float b03 = std::pow(1.0f - u, 3);
    float b13 = 3.0f * u * std::pow(1.0f - u, 2);
    float b23 = 3.0f * u * u * (1.0 - u);
    float b33 = u * u * u;

    return (b03 * p0_) + (b13 * c0_) + (b23 * c1_) + (b33 * p1_);
}

std::ostream &operator<<(std::ostream &os, const Bezier &obj)
{
    os << "( p0: " << obj.p0_ << ", c0: " << obj.c0_ << ", c1: " << obj.c1_ << ", p1: " << obj.p1_ << " )";
    return os;
}
