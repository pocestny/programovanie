#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <iomanip>

#include "gradient.h"
#include "kreslic.h"
#include "obrazok.h"
#include "tabulka.h"
#include "vektor.h"

using namespace std;
using namespace chrono;

/* **************************************
 *
 * pomocne funkcie
 *
 */

// nahodne cislo 0-1
double rnd() { return (double)(random() % (1 << 30)) / (double)(1 << 30); }

// normala v uzle (i,j)
// H je funkcia, ktora dava vysky
// s je rozmer mriezky
template <typename F>
Vec3 normala(F H, int i, int j, double s = 1) {
  Vec3 res;
  vector<Vec> dir{{0, 1},   {1, 1},  {1, 0},  {1, -1}, {0, -1},
                  {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}};
  for (int t = 0; t < dir.size() - 1; t++) {
    int i0 = i + dir[t].x, j0 = j + dir[t].y, i1 = i + dir[t + 1].x,
        j1 = j + dir[t + 1].y;
    res +=
        -1.0 *
        ((Vec3{s * dir[t].x, s * dir[t].y, H(i0, j0)} - Vec3{0, 0, H(i, j)}) ^
         (Vec3{s * dir[t + 1].x, s * dir[t + 1].y, H(i1, j1)} -
          Vec3{0, 0, H(i, j)}));
  }
  return res.normalize();
}

/* **************************************
 *
 * Perlin noise
 *
 */

struct Perlin {
  int n, d, m;  // rozmer obrazka, stride gridu, rozmer gridu
  Tabulka<double> H;
  Tabulka<Vec> G;

  Perlin(int _n, int _d) : n{_n}, d{_d}, m{1 + n / d}, H(n, n), G(m, m) {
    for (int i = 0; i < m; i++)
      for (int j = 0; j < m; j++) {
        double theta = rnd() * M_PI * 2.0;
        G(i, j) = {cos(theta), sin(theta)};
      }
    urob();
  }

  Perlin(int _n, int _d, const Tabulka<Vec>& _G)
      : n{_n}, d{_d}, m{1 + n / d}, H(n, n), G(_G) {
    urob();
  }

 private:
  void urob() {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        // transformuj z H-gridu do G-gridu
        Vec p{(double)i / (double)d, (double)(j) / (double)d};
        int o[2] = {(int)p.x, (int)p.y};

        double dot[4];
        for (int dx = 0; dx < 2; dx++)
          for (int dy = 0; dy < 2; dy++)
            dot[dx + 2 * dy] = (p - Vec{(double)o[0] + dx, (double)o[1] + dy}) *
                               G(o[0] + dx, o[1] + dy);

        Vec t{fade(p.x - o[0]), fade(p.y - o[1])};
        H(i, j) = bilinear(dot[0], dot[1], dot[2], dot[3], t);
      }
  }
  double fade(double t) { return t * t * t * (10 + t * (6 * t - 15)); }
};

/* **************************************
 *
 * Eroder: simuluje eroziu
 *
 */

struct Eroder {
  vector<Vec> trace;  // na kreslenie ciar kvapiek

  Tabulka<double> H;
  int n;
  Tabulka<double> E;

  const double zotrvacnost = 0.2;
  const double rozpustnost = 13;   // kapacita: kolko vie moda odniest
  const double usadzanie = 0.2;  // rychlost usadzania
  const double erozia = 0.5;
  const double gravitacia = 5;
  const double odparovanie = 0.0013;
  const double min_sklon = 0.1;
  const int lifetime = 150;
  const int numkvap = 350000;

  static const int r = 1;             // polomer erozie
  double vahy[2 * r + 1][2 * r + 1];  // vahy erozie

  Eroder(const Tabulka<double>& _H) : H(_H), n(H.n), E(n, n) {
    double sum = 0;
    for (int dx = 0; dx < 2 * r + 1; dx++)
      for (int dy = 0; dy < 2 * r + 1; dy++) {
        double dist = sqrt((r - dx) * (r - dx) + (r - dy) * (r - dy)) /
                      (sqrt(2) * (r + 1));
        double w = 0;
        if (dist < 1) w = (1 - dist);  // * (1 - dist);
        vahy[dx][dy] = w;
        sum += w;
      }
    for (int dx = 0; dx < 2 * r + 1; dx++)
      for (int dy = 0; dy < 2 * r + 1; dy++) vahy[dx][dy] /= sum;
  }

  void kvap() {
    trace.clear();

    Vec pos{rnd() * n, rnd() * n};
    while (vyska(pos) < -0.6) pos = Vec{rnd() * n, rnd() * n};

    // Vec dir{rnd(), rnd()};
    Vec dir{0, 0};

    double rychlost = 1;  // velocity - rychlost
    double voda = 1;      // objem vody
    double bahno = 0;     // objem usadeniny

    for (int t = 0; t < lifetime; t++) {
      trace.push_back(pos);
      int ix = pos.x, iy = pos.y;
      Vec p{pos.x - ix, pos.y - iy};  // pozicia v ramci gridu

      Vec3 e[4];  // normals
      for (int dx = 0; dx < 2; dx++)
        for (int dy = 0; dy < 2; dy++)
          e[dx + 2 * dy] =
              normala([this](int i, int j) { return H(i, j) + E(i, j); },
                      ix + dx, iy + dy);
      Vec3 norm = bilinear(e[0], e[1], e[2], e[3], p);

      Vec g{norm.x, norm.y};  // gradient
      g = g.normalize();

      dir = lerp(g, dir, zotrvacnost);
      if (dir.length() < 1e-25) break;
      dir.normalize();

      // cout<<pos.x<<" "<<pos.y<<" "<<dir.x<<" "<<dir.y<<endl;
      if (0) {
        cout << pos.x << " " << pos.y << " :: " << dir.x << " " << dir.y
             << "  ::: ";
        for (int dx = 0; dx < 2; dx++)
          for (int dy = 0; dy < 2; dy++) cout << H(ix + dx, iy + dy) << " ";
        cout << endl;
      }

      double h = vyska(pos);
      // cout<<"p:"<<pos<<" h:"<<h<<" dir:";
      pos += dir;
      double h_new = vyska(pos);
      // cout<<dir<<" pnew:"<<pos<<" hnew:"<<h_new<<endl;

      if (pos.x < 1 || pos.x >= n - 2 || pos.y < 1 || pos.y >= n - 2) break;

      double delta = h_new - h;
      //       cout<<g.x<<" "<<g.y<<") ("<<dir.x<<" "<<dir.y<<") "<<h_new<<"
      //       "<<h<<" "<<delta<<endl;

      double dasausadit =
          max(-delta, min_sklon) * rychlost * voda * rozpustnost;
      // cout<<setw(10)<<dasausadit<<" "<<setw(10)<<bahno<<endl;
      if (bahno > dasausadit || delta > 0) {
        double usadit;
        if (delta > 0)
          usadit = min(delta, bahno);
        else
          usadit = (bahno - dasausadit) * usadzanie;
        bahno -= usadit;
        if (0)
          cout << "dasa: " << dasausadit << " " << -delta << " " << rychlost
               << " " << voda << " " << bahno << " usadit:" << usadit << endl;
        // rozdistribuj bilinearne
        for (int dx = 0; dx < 2; dx++)
          for (int dy = 0; dy < 2; dy++) {
            E(ix + dx, iy + dy) += usadit * (dx * p.x + (1 - dx) * (1 - p.x)) *
                                   (dy * p.y + (1 - dy) * (1 - p.y));
            // cout<<"B"<<E(ix + dx, iy + dy)<<endl;
          }
      } else {
        double urvat = min((dasausadit - bahno) * erozia, -delta);
        if (0)
          cout << dasausadit << " " << bahno << " " << erozia << " " << (-delta)
               << " " << urvat << endl;

        for (int dx = 0; dx < 2 * r + 1; dx++)
          for (int dy = 0; dy < 2 * r + 1; dy++) {
            int i = ix - r + dx, j = iy - r + dy;
            double kusok = urvat * vahy[dx][dy];
            E(i, j) -= kusok;
            // cout<<"E("<<i<<","<<j<<") -= "<<kusok<<endl;
            // cout<<"E"<<E(i,j)<<endl;
            bahno += kusok;
          }
      }
      if (delta < 0) delta *= -1;
      rychlost = sqrt(rychlost * rychlost + delta * gravitacia);
      voda *= (1 - odparovanie);
    }
  }

  double vyska(Vec pos) {
    int ix = pos.x, iy = pos.y;
    Vec p{pos.x - ix, pos.y - iy};  // pozicia v ramci gridu
    double w[4];
    for (int dx = 0; dx < 2; dx++)
      for (int dy = 0; dy < 2; dy++)
        w[dx + 2 * dy] = H(ix + dx, iy + dy) + E(ix + dx, iy + dy);
    return bilinear(w[0], w[1], w[2], w[3], p);
  }
};

/* **************************************
 *
 * Renderer : zapise obrazok
 *
 */
struct Renderer {
  static const int heightmap = 1;
  static const int colored = 2;
  static const int normalmap = 4;
  static const int rendered = 8;
  static const int all = 15;

  Gradient gLand, gWater, gHeight, gNormal;

  double wl = -1e60, minl, maxl;

  const Tabulka<double>& H;
  Tabulka<double> N;
  Tabulka<Vec3> tHeightfield, tColored, tRendered, tNormal;
  Vec3 light;
  double normal_scale;
  Vec3 waterNormal;

  Renderer(const Tabulka<double>& _H)
      : H(_H),
        N(H.m, H.n),
        tHeightfield(H.m, H.n),
        tColored(H.m, H.n),
        tRendered(H.m, H.n),
        tNormal(H.m, H.n),
        light{-1, 1, 12},
        // normal_scale{1 / (double)H.n},
        normal_scale{0.08},
        waterNormal{0.044, 0.473, 0.505} {
    gLand = Gradient({{0, {0.028, 0.306, 0.007}},
                      {0.3, {0.92, 0.882, 0.343}},
                      {0.9, {0.264, 0.185, 0.029}},
                      {1, {1, 1, 1}}});
    gWater = Gradient({{0, {0.101, 0.258, 0.452}}, {1, {0.596, 0.682, 0.689}}});
    gHeight = Gradient({{0, {0, 0, 0}}, {1, {1, 1, 1}}});
    gNormal = Gradient({{0, {0, 0, 0}}, {1, {1, 1, 1}}});

    minl = 1e50, maxl = -1e50;
    for (int i = 0; i < H.m; i++)
      for (int j = 0; j < H.n; j++)
        if (H(i, j) < minl)
          minl = H(i, j);
        else if (H(i, j) > maxl)
          maxl = H(i, j);
  }

  void render(int co, string file) {
    if (co & heightmap) {
      tHeightfield.zmen([this](int i, int j) {
        return gHeight((H(i, j) - minl) / (maxl - minl));
      });
      stringstream ss;
      ss << file << "_heightmap.png";
      if (file.size() > 0) zapis(tHeightfield, ss.str().data());
    }

    if (co & colored || co & rendered) {
      tColored.zmen([this](int i, int j) {
        if (H(i, j) > wl)
          return gLand((H(i, j) - wl) / (maxl - wl));
        else
          return gWater((H(i, j) - minl) / (wl - minl));
      });
      stringstream ss;
      ss << file << "_colored.png";
      if (co & colored && file.size() > 0) zapis(tColored, ss.str().data());
    }

    double lo = 0.3;

    if (co & rendered || co & normalmap) {
      light.normalize();
      N.zmen([this](int i, int j) -> double {
        if (H(i, j) <= wl)
          return 1;
        else {
          double res =
              (light * (normala([this](int i, int j) { return H(i, j); }, i, j,
                                normal_scale)
                            .normalize()));
          return res;
        }
      });
      stringstream ss;
      ss << file << "_normal.png";

      if (co & normalmap) {
        tNormal.zmen([this, lo](int i, int j) {
          if (H(i, j) <= wl)
            return waterNormal;
          else {
            return gNormal( min(1.0, max(lo, N(i, j))) );
          }
        });
        if (file.size() > 0) zapis(tNormal, ss.str().data());
      }
    }

    if (co & rendered) {
      stringstream ss;
      ss << file << "_rendered.png";
      tRendered.zmen([this, lo](int i, int j) {
        // double lo = 0.6, hi = 1.1;
        double coeff;
        if (H(i, j) <= wl)
          coeff = 1;  // s + 0.5 * (lo + hi);
        else {
          coeff = 0.7+0.3*(min(1.0, max(lo, N(i, j))) - lo)/(1.0-lo);
          //coeff = (max(lo, N(i, j)) - lo) / (1.0 - lo);
          // coeff =  s + lo + (hi - lo) * ((N(i, j) - mi) / (ma - mi));
        }
        return coeff * tColored(i, j);
      });
      if (file.size() > 0) zapis(tRendered, ss.str().data());
    }
  }

  void zapis(Tabulka<Vec3>& T, const char* fname) {
    vector<unsigned char> data(T.m * T.n * 4);
    for (int i = 0; i < T.m; i++)
      for (int j = 0; j < T.n; j++) {
        int offs = 4 * ((T.n - j - 1) * T.n + i);
        data[offs++] = min(255 * T(i, j).x, 255.0);
        data[offs++] = min(255 * T(i, j).y, 255.0);
        data[offs++] = min(255 * T(i, j).z, 255.0);
        data[offs++] = 255;
      }
    zapis_rgba_png(T.n, T.m, data.data(), fname);
  }
};

/* **************************************
 *
 * hlavny program
 *
 */

Tabulka<double> blur(Tabulka<double>& H, int r) {
  Tabulka<double> res = H;
  for (int i = r / 2; i < H.n - r / 2; i++)
    for (int j = r / 2; j < H.n - r / 2; j++) {
      double avg = 0;
      for (int k = i - r / 2; k < i + r / 2; k++)
        for (int l = j - r / 2; l < j + r / 2; l++) avg += H(k, l);
      res(i, j) = avg / (r * r);
    }
  return res;
}


int main(int argc, char** argv) {
  uint64_t seed =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch())
          .count();
  if (argc > 1) {
    stringstream ss(argv[1]);
    ss >> seed;
  } else {
    cout << "seed: " << seed << endl;
  }
  srandom(seed);

  int n = 2048;
  Tabulka<double> H(n, n), P(n, n);
  for (int t = 2; t < n; t *= 2) {
    auto x = Perlin(n, t).H;
    if (t >= 16) {
      H *= 0.54;
      H += x;
    } else {
      P *= 0.54;
      P += x;
    }
  }

  auto okraj = [n](int i, int j, double x) {
    double dist = sqrt((n / 2 - i) * (n / 2 - i) + (n / 2 - j) * (n / 2 - j));
    dist = (2 * dist) / (double)n;
    return 5 * x - 3.5 * pow(dist, 5);
  };

  double dno = 1e50;
  H.zmen([&H, okraj, &dno](int i, int j) {
    double x = okraj(i, j, H(i, j));
    if (x < dno) dno = x;
    return x;
  });

  double wl = -0.6;

  H.zmen([&H](int i, int j) {
      double x=H(i,j);
      if (x>0)
      x=3*pow(x,1.8);
      return x;
      });


  cout<<"mam mapu\n";

  Eroder e(H);
  vector<vector<Vec>> huh;
  if (1)
    for (int i = 0; i < e.numkvap; i++) {
      e.kvap();
      if (i%5000==0) {cout<<"kvap "<<flush;}
      if (i<20000) huh.push_back(e.trace);
    }

  //blur(e.E,4);

  e.H.zmen([&e, &P, &H, wl, dno](int i, int j) {
    double x = e.H(i, j);
    // x = x + max(dno, 1 * e.E(i, j)) + 0.3 * P(i, j);
    x = x + 0.7 * e.E(i, j) + 0.22 * P(i, j);
    // x = x +  0.9* e.E(i, j);
    // cout<<"X"<<e.E(i,j)<<endl;
    /*
    if (x < wl + 1e-5)
      x = H(i, j);
    else {
      double f = x - wl;
      x = wl + 3 * f;
    }
    */
      //double f = x - wl;
      //x = wl +  * f*f;
    return x;
  });

  cout<<"\npisem\n";
  Renderer r(e.H);
  r.gWater = Gradient("gradient/water1.gpf");
  r.gLand = Gradient("gradient/land1.gpf");
  /*r.gHeight = Gradient(
      {{0, {0, 0, 0}}, {0.499, {0, 0, 0}}, {0.501, {1, 1, 0}}, {1, {1, 1, 0}}});
  */
  r.wl = wl;
  stringstream ss;
  ss << seed;
  r.render(Renderer::all, ss.str());

  if (1) {
    Tabulka<Vec3> T(n, n);
    Gradient gq({{0, {1, 0, 1}}, {1, {0, 1, 1}}});
#if 1
    for (auto h : huh)
      for (int i = 1; i < h.size(); i++)
        line(T, h[i - 1].x, h[i - 1].y, h[i].x, h[i].y,
             // gq((double)i / double(h.size())));
             gq((double)i / double(e.lifetime)));
#endif
    vector<unsigned char> data(T.m * T.n * 4);
    for (int i = 0; i < T.m; i++)
      for (int j = 0; j < T.n; j++) {
        int offs = 4 * ((T.n - j - 1) * T.n + i);
        data[offs++] = 255 * T(i, j).x;
        data[offs++] = 255 * T(i, j).y;
        data[offs++] = 255 * T(i, j).z;
        data[offs++] = T(i, j).z * 255;
      }
    zapis_rgba_png(T.n, T.m, data.data(), "droplets.png");
  }
}
