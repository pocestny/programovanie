#ifndef __KRESLIC_H__
#define __KRESLIC_H__
#include "tabulka.h"
#include "vektor.h"

void line(Tabulka<Vec3> &T, double x1, double y1, double x2, double y2,
          Vec3 f = {1, 0, 0}) {
  using namespace std;
  T(x1, y1) = f;
  T(x2, y2) = f;

  if (abs(x2 - x1) < 0.00001) {
    if (y1 > y2) {
      int k = y1;
      y1 = y2;
      y2 = k;
    }
    for (int i = y1; i <= y2; i++) T(x1, i) = f;
    return;
  }
  if (abs(y2 - y1) < 0.00001) {
    if (x1 > x2) {
      int k = x1;
      x1 = x2;
      x2 = k;
    }
    for (int i = x1; i <= x2; i++) T(i, y1) = f;
    return;
  }
  if (x1 > x2) {
    int k = x1;
    x1 = x2;
    x2 = k;
    k = y1;
    y1 = y2;
    y2 = k;
  }
  double s = (y2 - y1) / (x2 - x1);
  if (abs(s) >= -1 && abs(s) <= 1) {
    double dx = ((int)x1) + 0.5 - x1;
    for (int i = 0; i < (int)x2 - (int)x1; i++)
      T(x1 + 0.5 + i, y1 + (dx + i) * s) = f;
  } else {
    if (y1 > y2) {
      int k = x1;
      x1 = x2;
      x2 = k;
      k = y1;
      y1 = y2;
      y2 = k;
    }
    s = 1 / s;
    double dy = ((int)y1) + 0.5 - y1;
    for (int i = 0; i < (int)y2 - (int)y1; i++)
      T(x1 + (dy + i) * s, y1 + 0.5 + i) = f;
  }
}

#endif
