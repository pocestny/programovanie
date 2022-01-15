#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> a;

int max(vector<int> &a) {
  int res = a[0];
  for (int i = 1; i < a.size(); i++)
    if (a[i] > res) res = a[i];
  return res;
}

bool test(int k) {
  int sum = 0;
  for (int i = 0; i < n; i++)
    if (a[i] > k) sum += a[i] - k;
  return sum >= m;
}

int main() {
  cin >> n >> m;
  a.resize(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  ;
  int l = 0, x, r = max(a);
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
