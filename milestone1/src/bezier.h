#pragma once
#include <vector>
#include "vect/vect.h"

class Bezier {
protected:
    Vect p0_;
    Vect c0_;
    Vect c1_;
    Vect p1_;

public:
    Bezier(Vect p0, Vect c0, Vect c1, Vect p1);
    Bezier(const Bezier &other);
    Bezier(Bezier &&other);
    Bezier &operator=(const Bezier &other);
    Bezier &operator=(Bezier &&other);
    virtual ~Bezier() {};

    Vect operator[](int i);
    std::vector<Bezier> Subdivide();
    Vect FindPoint(float u);

    friend std::ostream &operator<<(std::ostream &os, const Bezier &obj);
};

