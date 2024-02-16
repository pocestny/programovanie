#include <iostream>
using namespace std;

int nuly(int n) {
  int z = 0;
  while (n > 1) {
    for (int i = 5; i <= n; i = i * 5)
      if (n % i == 0) z++;
    n--;
  }
  return z;
}

int main() {
  int x;
  cin >> x;
  int l = 1, r = 1, m;
  while (nuly(r) < x) r = 2 * r;
  while (l < r - 1) {
    // cout << l << " " << r << endl;
    m = (l + r) / 2;
    if (nuly(m) < x)
      l = m;
    else
      r = m;
  }
  if (nuly(l) >= x)
    cout << l << endl;
  else
    cout << r << endl;
}
