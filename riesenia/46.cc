#include <iostream>
using namespace std;

int main() {
  int n, m, i, j;
  cin >> n;
  int a[n], s[n];
  for (i = 0; i < n; i++) cin >> a[i];
  m = 0;
  for (i = 0; i < n; i++) {
    while (m > 0 && a[s[m - 1]] >= a[i]) m--;
    if (m == 0)
      cout << -1 << " ";
    else
      cout << s[m - 1] << " ";
    s[m] = i;
    m++;
  }
  cout << endl;
}
