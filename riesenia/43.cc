#include <iostream>
using namespace std;

int main() {
  int n, i, j, cnt = 0, k;
  cin >> n;
  int a[n];
  for (i = 0; i < n; i++) cin >> a[i];
  cin >> k;

  i = 0;
  j = 0;

  while (true) {
    while (j < n && a[j] - a[i] < k) j++;
    if (j == n) break;
    if (a[j] - a[i] == k) cnt++;
    while (j < n && a[j] - a[i] == k) j++;
    if (j == n) break;
    while (i < j && a[j] - a[i] > k) i++;
    if (i == j) continue;
    if (a[j] - a[i] == k) cnt++;
    while (i < j && a[j] - a[i] == k) i++;
  }

  cout << cnt << endl;
}
