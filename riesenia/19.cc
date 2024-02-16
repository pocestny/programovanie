#include <iostream>
using namespace std;

int main() {
  int i, j, k, n;
  cin >> n;
  int a[n];
  i = 0;
  while (i < n) {
    cin >> a[i];
    i = i + 1;
  }
  bool found;
  found = false;
  k = n;
  while (!found && k > 0) {
    i = 0;
    while (!found && i <= n - k) {
      j = i;
      while (a[j] >= k && j < i + k) j = j + 1;
      if (j == i + k) {
        cout << k << endl;
        found = true;
      }
      i = i + 1;
    }
    k = k - 1;
  }
}
