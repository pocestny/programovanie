#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Dvojica {
  int x, pos;
  bool operator<(Dvojica d) {
    if (x != d.x) return x < d.x;
    return pos < d.pos;
  }
};

int main() {
  int n, k;
  vector<Dvojica> a;

  cin >> n >> k;
  a.resize(n + 1);
  a[0] = {0, 0};

  int sum = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x;
    a[i].pos = i;
  }
  sort(a.begin(), a.end());

  int res = 0, i, j = 0;
  for (i = 0; i < n; i++) {
    if (i == 0 || a[i].x != a[i - 1].x) j = i;
    while (j <= n && a[j].x == a[i].x && a[j].pos - a[i].pos <= k) j++;
    res += j - i - 1;
  }
  cout << res << endl;
}
