#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Sipka {
  int j, t;
};

struct Info {
  int deg, t;
  bool operator<(const Info& x) const {
    if (deg != x.deg) return deg < x.deg;
    return t < x.t;
  }
};

int main() {
  int m, n;
  cin >> n >> m;

  vector<Info> a(n);
  for (int i = 0; i < n; i++) {
    a[i].t = 0;
    a[i].deg = 0;
  }
  vector<vector<Sipka>> G(n);
  while (m-- > 0) {
    int x, y, t;
    cin >> x >> y >> t;
    G[x].push_back(Sipka{y, t});
    a[y].deg++;
  }

  multiset<int, function<bool(int, int)>> s(
      [&](int i, int j) { return a[i] < a[j]; });
  for (int i = 0; i < n; i++) s.insert(i);

  vector<int> ts(1, 0);
  vector<vector<int>> out(1);

  while (s.size() > 0) {
    int v = *s.begin();

    if (a[v].deg > 0) {
      cout << "neda sa" << endl;
      exit(0);
    }
    if (a[v].t != ts.back()) {
      out.push_back(vector<int>{});
      ts.push_back(a[v].t);
    }
    out.back().push_back(v);
    s.erase(s.begin());
    for (Sipka r : G[v]) {
      s.erase(r.j);
      a[r.j].deg--;
      a[r.j].t = max(a[r.j].t, a[v].t + r.t);
      s.insert(r.j);
    }
  }

  for (int i = 0; i < ts.size(); i++) {
    cout << 1 + ts[i] << ". den:";
    for (int x : out[i]) cout << " " << x;
    cout << endl;
  }
}
