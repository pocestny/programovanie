#include <iostream>
#include <vector>
using namespace std;

int n, b;
vector<int> p, m;

bool test(int k) {
  int sum = 0;
  for (int i = 0; i < n; i++)
    if (p[i] < k) sum += m[i] * (k - p[i]);
  return sum <= b;
}

int min(vector<int> &a) {
  int res = a[0];
  for (int i = 1; i < a.size(); i++)
    if (a[i] < res) res = a[i];
  return res;
}

int max(vector<int> &a) {
  int res = a[0];
  for (int i = 1; i < a.size(); i++)
    if (a[i] > res) res = a[i];
  return res;
}

int main() {
  cin >> n >> b;
  p.resize(n);
  m.resize(n);
  for (int i = 0; i < n; i++) cin >> p[i] >> m[i];
  int l = min(p), x, r = max(p) + b;
  while (l < r - 1) {
    x = (l + r) / 2;
    if (test(x))
      l = x;
    else
      r = x;
  }
  if (test(r))
    cout << r << endl;
  else
    cout << l << endl;
}
