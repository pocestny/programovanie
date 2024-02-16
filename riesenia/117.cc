#ifndef __VEKTOR_H__
#define __VEKTOR_H__
#include <cmath>
#include <ostream>

// 2D
struct Vec {
  double x = 0, y = 0;
  double length() { return sqrt(x * x + y * y); }
  Vec& normalize() {
    double l = length();
    if (l >= 1e-30) {
      x /= l;
      y /= l;
    }
    return *this;
  }
  Vec& operator+=(const Vec& v) {
    x += v.x;
    y += v.y;
    return *this;
  }
  Vec& operator-=(const Vec& v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }
  Vec& operator*=(const double v) {
    x *= v;
    y *= v;
    return *this;
  }
  void clip(double lo = 0, double hi = 1) {
    if (x < lo) x = lo;
    if (x > hi) x = hi;
    if (y < lo) y = lo;
    if (y > hi) y = hi;
  }
};

bool operator== (const Vec&a, const Vec&b) {
  return a.x==b.x && a.y==b.y;
}

Vec operator+(const Vec& a, const Vec& b) { return Vec{a.x + b.x, a.y + b.y}; }
Vec operator-(const Vec& a, const Vec& b) { return Vec{a.x - b.x, a.y - b.y}; }
Vec operator*(const Vec& a, const double v) { return Vec{a.x * v, a.y * v}; }
Vec operator*(const double v, const Vec& a) { return Vec{a.x * v, a.y * v}; }
// skalarny sucin
double operator*(const Vec& a, const Vec& b) { return a.x * b.x + a.y * b.y; }

std::ostream &operator<<(std::ostream &s, const Vec &v) {
  s << "[ " << v.x << ", " << v.y << " ]";
  return s;
}

// 3D
struct Vec3 {
  double x = 0, y = 0, z = 0;
  double length() { return sqrt(x * x + y * y + z * z); }
  Vec3& normalize() {
    double l = length();
    if (l >= 1e-30) {
      x /= l;
      y /= l;
      z /= l;
    }
    return *this;
  }
  Vec3& operator+=(const Vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  Vec3& operator-=(const Vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  Vec3& operator*=(const double v) {
    x *= v;
    y *= v;
    z *= v;
    return *this;
  }
  void clip(double lo = 0, double hi = 1) {
    if (x < lo) x = lo;
    if (x > hi) x = hi;
    if (y < lo) y = lo;
    if (y > hi) y = hi;
    if (z < lo) z = lo;
    if (z > hi) z = hi;
  }
};

bool operator== (const Vec3&a, const Vec3&b) {
  return a.x==b.x && a.y==b.y && a.z==b.z;
}

Vec3 operator+(const Vec3& a, const Vec3& b) {
  return Vec3{a.x + b.x, a.y + b.y, a.z + b.z};
}
Vec3 operator-(const Vec3& a, const Vec3& b) {
  return Vec3{a.x - b.x, a.y - b.y, a.z - b.z};
}
Vec3 operator*(const Vec3& a, const double v) {
  return Vec3{a.x * v, a.y * v, a.z * v};
}
Vec3 operator*(const double v, const Vec3& a) {
  return Vec3{a.x * v, a.y * v, a.z * v};
}
// skalarny sucin
double operator*(const Vec3& a, const Vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
// vektorovy sucin
Vec3 operator^(const Vec3& a, const Vec3& b) {
  return Vec3{a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x};
}

std::ostream &operator<<(std::ostream &s, const Vec3 &v) {
  s << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
  return s;
}

#endif
