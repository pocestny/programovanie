#ifndef __GRADIENT_H__
#define __GRADIENT_H__

#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "vektor.h"

struct Stop {
  double t;
  Vec3 rgb;
};

struct Gradient {
  std::vector<Stop> stops;
  Gradient(const std::vector<Stop>& _stops = std::vector<Stop>{}) {
    stops = _stops;
  }

  Gradient(const std::string& fname);

  Vec3 operator()(double t) const;
};

#endif
