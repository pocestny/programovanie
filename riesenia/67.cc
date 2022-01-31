#include <iostream>
using namespace std;

int najdi(int n, int *a, int x) {
  int l = 0, r = n - 1, m;
  if (a[l] > x) return -1;
  if (a[l] == x) return l;
  if (a[r] < x) return n;
  while (l < r - 1) {
    m = (l + r) / 2;
    if (a[m] >= x)
      r = m;
    else
      l = m;
  }
  if (a[r] >= x) return r;
  return r + 1;
}

int pocet(int n, int *a, int k) { 
  return najdi(n, a, k + 1) - najdi(n, a, k); 
}

int main() {
  int n, *a;
  cin >> n;
  a = new int[n];
  for (int i = 0; i < n; i++) cin >> a[i];
  int k;
  cin >> k;
  cout << pocet(n, a, k) << endl;
  delete[] a;
}
