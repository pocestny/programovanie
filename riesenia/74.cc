#include <iostream>
#include <vector>

using namespace std;

vector<int> V;
int n, k;

bool test(int t) {
  int x = 0;
  for (int i = 0; i < n; i++)
    if (V[i] > t) {
      x += (V[i] - t) / k;
      if ((V[i] - t) % k) x++;
    }
  return (x <= t);
}

void search(int l, int r) {
  if (r - l < 10) {
    for (int i = l; i <= r; i++)
      if (test(i)) {
        cout << i << endl;
        exit(0);
      }
  } else {
    int m = (l + r) / 2;
    if (!test(m))
      search(m, r);
    else
      search(l, m);
  }
}

int main() {
  cin >> n;
  V.resize(n);
  int max = 0;
  for (int i = 0; i < n; i++) {
    cin >> V[i];
    if (V[i] > max) max = V[i];
  }
  cin >> k;
  k--;

  if (k == 0)
    cout << max << endl;
  else
    search(0, max);
}
