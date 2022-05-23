#include <iostream>
using namespace std;

int a[10000];

void rob(int i, int n, int m, int k) {
  if (i == n && m == 0 && k == 0) {
    int j;
    for (j = 0; j < n; j++) cout << a[j] << " ";
    cout << endl;
  } else {
    if (n - i >= m + k) {
      a[i] = 0;
      rob(i + 1, n, m, k);
    }
    if (m > 0) {
      a[i] = 1;
      rob(i + 1, n, m - 1, k);
    }
    if (k > 0) {
      a[i] = 2;
      rob(i + 1, n, m, k - 1);
    }
  }
}

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  rob(0, n, m, k);
}
