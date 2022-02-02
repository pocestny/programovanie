#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n;
  vector<int> a, x;
  cin >> n;
  a.resize(n);
  x.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    x[i] = i;
  }
  sort(x.begin(), x.end(), [&a](int i, int j) { return a[i] < a[j]; });
  for (int i = 0; i < n; i++) a[x[i]] = i + 1;
  for (int i = 0; i < n; i++) cout << a[i] << " ";
  cout << endl;
}
