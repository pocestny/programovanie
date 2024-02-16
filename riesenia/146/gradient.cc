#include "gradient.h"

#include <algorithm>

Gradient::Gradient(const std::string& fname) {
  using namespace std;
  ifstream f(fname);
  string line;
  while (getline(f, line)) {
    if (line[0] == '#') continue;
    stringstream ss(line);
    Stop s;
    ss >> s.t;
    double r, g, b;
    ss >> r >> g >> b;
    s.rgb = Vec3{r, g, b};
    stops.push_back(s);
  }
}

Vec3 Gradient::operator()(double t) const {
  using namespace std;
  t = fmod(t, 1);
  auto it = lower_bound(stops.begin(), stops.end(), Stop{t, {}},
                        [](Stop a, Stop b) { return a.t < b.t; });

  if (it == stops.begin()) return stops[0].rgb;
  Vec3 a = (it)->rgb, b = (it - 1)->rgb;
  t = (t - (it - 1)->t) / (it->t - (it - 1)->t);

  return lerp(b, a, t);
}
