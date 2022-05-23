#include <iostream>
#include <set>
using namespace std;

int n, k, a;

int val(int d) {
  if (d < a) return 0;
  return (d + 1) / (a + 1);
}

int main() {
  cin >> n >> k >> a;

  int m, cnt = 0;
  cin >> m;

  set<int> hits;
  int avail = val(n);
  hits.insert(0);
  hits.insert(n + 1);

  while (m-- >= 0) {
    int x;
    cin >> x;
    cnt++;
    auto tmp = hits.lower_bound(x);
    int i2 = *tmp;
    tmp--;
    int i1 = *tmp;
    avail -= val(i2 - i1 - 1);
    avail += val(x - i1 - 1) + val(i2 - x - 1);
    hits.insert(x);

    if (avail < k) {
      cout << cnt << endl;
      exit(0);
    }
  }
  cout << "-1\n";
}
