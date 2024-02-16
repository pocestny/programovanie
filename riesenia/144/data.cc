#include "data.h"
using namespace std;

InOut Pattern::sample(int s) {
  if (s == -1) return all();

  InOut res(2, 1, s);
  uniform_real_distribution<> dis(-1.0, 1.0);
  for (int i = 0; i < s; i++) {
    double x = dis(rnd), y = dis(rnd);
    res.in(0, i) = x;
    res.in(1, i) = y;
    res.out(0, i) = f(x, y);
  }
  return res;
}

InOut Pattern::all() {
  int n = dim;
  InOut res(2, 1, n * n);
  double step = 2.0 / (double)n;
  int k = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      double y = 1.0 - 0.5 * step - i * step, x = -1.0 + 0.5 * step + j * step,
             v = f(x, y);
      res.in(0, k) = x;
      res.in(1, k) = y;
      res.out(0, k) = v;
      k++;
    }
  return res;
}

Pattern::F verticalPattern(double h) {
  return [h](double x, double y) { return (x < h) ? -1.0 : 1.0; };
}

Pattern::F squarePattern(int n) {
  return [n](double x, double y) {
    return ((int)((x + 1.0) * 0.5 * n) % 2 == (int)((y + 1.0) * 0.5 * n) % 2)
               ? -1.0
               : 1.0;
  };
}

Pattern::F circlePattern(double r) {
  return
      [r](double x, double y) { return (x * x + y * y <= r * r) ? -1.0 : 1.0; };
}

Pattern::F heartPattern() {
  return [](double x, double y) {
    x = (x + 1) * 0.5, y = (y + 1) * 0.5;
    Num t = asin(pow(fabs(x - 0.5) * 34.0 / 16.0, 1.0 / 3.0));
    auto yy = [](Num t) {
      return 0.55 + (13.0 * cos(t) - 5.0 * cos(2.0 * t) - 2.0 * cos(3.0 * t) -
                     cos(4.0 * t)) /
                        34.0;
    };
    Num y1 = yy(t);
    Num y2 = yy(M_PI - t);
    return ((y <= y1) && (y >= y2)) ? -1.0 : 1.0;
  };
}
