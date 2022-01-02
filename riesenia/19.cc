#include <iostream>
using namespace std;

int main() {
  int i, j, k, n;
  cin >> n;
  int a[n];
  for (i = 0; i < n; i++) cin >> a[i];
  bool found = false;
  for (k = n; !found && k > 0; k--) {
    for (i = 0; !found && i <= n - k; i++) {
      j = i;
      while (a[j] >= k && j < i + k) j++;
      if (j == i + k) {
        cout << k << endl;
        found = true;
      }
    }
  }
}
