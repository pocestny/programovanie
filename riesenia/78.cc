#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n;
  vector<int> a;
  cin >> n;
  a.resize(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a.begin(), a.end(), [](int a, int b) {
    if (a % 2 != b % 2) return (a % 2) < (b % 2);
    if (a % 2 == 0) return a < b;
    return a > b;
  });
  for (int i = 0; i < n; i++) cout << a[i] << " ";
  cout << endl;
}
