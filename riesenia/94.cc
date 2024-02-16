#include "obrazok.h"
#include <algorithm>
#include <complex>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
using Byte = unsigned char;
using Int = unsigned long long int;
using Real = long double;
using Complex = complex<Real>;

const Int R = (Int)1 << 32;
const Int N = 100000;
Real d;  // ako rychlo rotuje paleta

struct RGBA {
  Byte r, g, b, a;
  RGBA(Byte _r = 255, Byte _g = 255, Byte _b = 255, Byte _a = 255) {
    r = _r;
    g = _g;
    b = _b;
    a = _a;
  }

  RGBA(const char* hex) {  // #rrggbb[aa]
    unsigned int val = 0;
    for (auto s = hex + 1; *s != 0; s++) {
      Byte c;
      if (*s >= '0' && *s <= '9')
        c = (*s) - '0';
      else if (*s >= 'a' && *s <= 'f')
        c = (*s) - 'a' + 10;
      else if (*s >= 'A' && *s <= 'F')
        c = (*s) - 'A' + 10;
      val = (val << 4) | c;
    }
    if (val < (1 << 25)) val = (val << 8) | 255;
    r = (Byte)(val >> 24);
    g = (Byte)((val >> 16) & 255);
    b = (Byte)((val >> 8) & 255);
    a = (Byte)(val & 255);
  }
};

struct Stop {
  Real t;
  RGBA f;
};

struct Gradient {
  vector<Stop> stops;
  Gradient(const vector<Stop>& _stops) { stops = _stops; }
  RGBA operator()(Real t) {
    t = fmod(t, 1);
    RGBA x;
    auto it = lower_bound(stops.begin(), stops.end(), Stop{t, {}},
                          [](Stop a, Stop b) { return a.t < b.t; });

    if (it == stops.begin()) return stops[0].f;
    RGBA a = (it)->f, b = (it - 1)->f;
    t = (t - (it - 1)->t) / (it->t - (it - 1)->t);

    x.r = (Byte)(t * a.r + (1 - t) * b.r);
    x.g = (Byte)(t * a.g + (1 - t) * b.g);
    x.b = (Byte)(t * a.b + (1 - t) * b.b);
    return x;
  }
};

struct Point {
  Real z;
  Int n;
};

struct Tabulka {
  int w, h;
  vector<Point> p;

  Tabulka(int _h, int _w) {
    w = _w;
    h = _h;
    p.resize(w * h);
  }
  Point& operator()(int r, int s) { return p[r * w + s]; }

  void zapis(Gradient& g) {
    vector<RGBA> c(h * w);

    map<Int, Real> lo, hi;
    Int minn = N, maxn = 0;

    for (auto x : p) {
      if (minn > x.n) minn = x.n;
      if (maxn < x.n) maxn = x.n;
      if (lo.count(x.n) == 0 || lo[x.n] > x.z) lo[x.n] = x.z;
      if (hi[x.n] < x.z) hi[x.n] = x.z;
    }

    for (int i = 0; i < h * w; i++) {
      if (p[i].n >= N)
        c[i] = {0, 0, 0, 255};
      else {
        Real v = p[i].n - minn + 1 -
                   (p[i].z - lo[p[i].n]) / (hi[p[i].n] - lo[p[i].n]);
        v = d * v / (maxn - minn + 1);
        c[i] = g(v);
      }
    }
    zapis_rgba_png(h, w, c.data(), "94.png");
  }
};

int main() {
  Gradient g({{0.0, RGBA(0, 7, 100)},
              {0.16, RGBA(32, 107, 203)},
              {0.42, RGBA(237, 255, 255)},
              {0.6425, RGBA(255, 170, 0)},
              {0.8575, RGBA(0, 2, 0)},
              {1.0, RGBA(0, 7, 100)}});

  int sirka = 1600, vyska = 1200;
  Complex stred;
  Real m;

  cin >> stred >> m >> d;
  Tabulka obrazok(vyska, sirka);
  Real pixel = 1 / ((Real)sirka * m);

  for (int i = 0; i < vyska; i++)
    for (int j = 0; j < sirka; j++) {
      Complex c = stred + Complex(j - sirka / 2, i - vyska / 2) * pixel;
      Int iter = 0;
      Complex z = c;
      while (norm(z) <= R && iter < N) {
        z = z * z + c;
        iter++;
      }
      obrazok(vyska - 1 - i, j) = Point{log(norm(z)), iter};
    }
  obrazok.zapis(g);
}
