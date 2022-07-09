#include <iostream>
using namespace std;
int main() {
  int n, i, j;
  cin >> n;
  int a[n + 1];
  a[0] = 0;
  cin >> a[1];
  for (i = 2; i <= n; i++) {
    cin >> a[i];
    a[i] = a[i] + a[i - 1];
  }
  while (n > 0) {
    cin >> i >> j;
    cout << a[j+1] - a[i] << endl;
    n--;
  }
}
