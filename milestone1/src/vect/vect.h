#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>

class Vect {
 public:
  float x;
  float y;
  float z;

  Vect(float in_x, float in_y, float in_z) : x(in_x), y(in_y), z(in_z) {}

  Vect(float in_x, float in_y) : x(in_x), y(in_y), z(0) {}

  Vect() : x(0), y(0), z(0) {}

  // copy constructor
  Vect(const Vect& v) : x(v.x), y(v.y), z(v.z) {}

  // assignment operator
  Vect& operator=(const Vect& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }

  // move constructor
  Vect(const Vect&& v) noexcept : x(v.x), y(v.y), z(v.z) {}

  // move assignment operator
  Vect& operator=(const Vect&& v) noexcept {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }

  float operator[](int i) {
    if (i == 0)
      return x;
    else if (i == 1)
      return y;
    else if (i == 2)
      return z;
    else
      return 0;
  }

  bool operator==(Vect v) { return x == v.x && y == v.y && z == v.z; }

  // Vect addition
  Vect operator+(Vect v) { return Vect(x + v.x, y + v.y, z + v.z); }

  // Vect subtraction
  Vect operator-(Vect v) { return Vect(x - v.x, y - v.y, z - v.z); }

  // negation is just scaling by -1.
  Vect operator-() { return Vect(-x, -y, -z); }

  // Vect scaling
  Vect operator*(float scaleFactor) {
    return Vect(x * scaleFactor, y * scaleFactor, z * scaleFactor);
  }

  // dot product
  float operator*(Vect v) { return x * v.x + y * v.y + z * v.z; }

  // magnitude
  float mag() { return (float)std::sqrt(x * x + y * y + z * z); }

  float slope() { return y / x; }

  Vect normalize() {
    float m = mag();
    return Vect(x / m, y / m, z / m);
  }
  // Correct move constructor
Vect(Vect&& v) noexcept : x(v.x), y(v.y), z(v.z) {}

// Correct move assignment operator
Vect& operator=(Vect&& v) noexcept {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}
   // Cross product of two vectors
    Vect cross(const Vect& other) const {
        return Vect(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
      // Define the equality operator
    bool operator==(const Vect& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    // Define the inequality operator using the equality operator
    bool operator!=(const Vect& other) const {
        return !(*this == other);
    }

  float projectOnto(Vect u) { return ((*this) * u) / u.mag(); }

  friend std::ostream& operator<<(std::ostream& os, const Vect& obj);
};

Vect operator*(float scaleFactor, Vect v);
