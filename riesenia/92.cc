#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Deg {
  int i, deg;
  bool operator<(const Deg& x) const {
    if (deg != x.deg) return deg < x.deg;
    return i < x.i;
  }
};

int main() {
  int m, n;
  cin >> n >> m;

  vector<Deg> inD(n);
  for (int i = 0; i < n; i++) {
    inD[i].i = i;
    inD[i].deg = 0;
  }
  vector<vector<int>> G(n);
  while (m-- > 0) {
    int x, y;
    cin >> x >> y;
    G[x].push_back(y);
    inD[y].deg++;
  }
  set<Deg> s;
  for (int i = 0; i < n; i++) s.insert(inD[i]);

  vector<int> out;
  while (s.size() > 0) {
    Deg v = *s.begin();
    if (v.deg > 0) {
      cout << "neda sa" << endl;
      exit(0);
    }
    out.push_back(v.i);
    s.erase(s.begin());
    for (int w : G[v.i]) {
      s.erase(inD[w]);
      inD[w].deg--;
      s.insert(inD[w]);
    }
  }
  for (int x : out) cout << x << " ";
  cout << endl;
}
