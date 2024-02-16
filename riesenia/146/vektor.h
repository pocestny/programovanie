#ifndef __VEKTOR_H__
#define __VEKTOR_H__
#include <cmath>
#include <ostream>

// 2D
struct Vec {
  double x = 0, y = 0;
  double length() { return sqrt(x * x + y * y); }
  Vec& normalize(); 
  Vec& operator+=(const Vec& v) ;
  Vec& operator-=(const Vec& v) ;
  Vec& operator*=(const double v) ;
  void clip(double lo = 0, double hi = 1) ;
};

bool operator==(const Vec& a, const Vec& b);

Vec operator+(const Vec& a, const Vec& b);
Vec operator-(const Vec& a, const Vec& b);
Vec operator*(const Vec& a, const double v);
Vec operator*(const double v, const Vec& a);
// skalarny sucin
double operator*(const Vec& a, const Vec& b);

std::ostream& operator<<(std::ostream& s, const Vec& v);

// 3D
struct Vec3 {
  double x = 0, y = 0, z = 0;
  double length() { return sqrt(x * x + y * y + z * z); }
  Vec3& normalize();
  Vec3& operator+=(const Vec3& v) ;
  Vec3& operator-=(const Vec3& v) ;
  Vec3& operator*=(const double v) ;
  void clip(double lo = 0, double hi = 1) ;
};

bool operator==(const Vec3& a, const Vec3& b);
Vec3 operator+(const Vec3& a, const Vec3& b) ;
Vec3 operator-(const Vec3& a, const Vec3& b) ;
Vec3 operator*(const Vec3& a, const double v) ;
Vec3 operator*(const double v, const Vec3& a) ;
// skalarny sucin
double operator*(const Vec3& a, const Vec3& b) ;
// vektorovy sucin
Vec3 operator^(const Vec3& a, const Vec3& b) ;

std::ostream& operator<<(std::ostream& s, const Vec3& v) ;

template <typename T>
T lerp(const T& v0, const T& v1, double t) {
  return (1 - t) * v0 + t * v1;
}

#endif
