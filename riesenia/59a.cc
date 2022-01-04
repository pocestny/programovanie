#include <iostream>
using namespace std;

void posun(int n, int *a, int k) {
  int *b = new int[n];
  int i;
  for (i = 0; i < n; i++) b[i] = a[i];
  for (i = 0; i < n; i++) a[i] = b[(i + k) % n];
  delete[] b;
}

int main() {
  int k, n, i;
  cin >> n;
  int *a = new int[n];
  for (i = 0; i < n; i++) cin >> a[i];
  cin >> k;
  posun(n, a, k);
  for (i = 0; i < n; i++) cout << a[i] << " ";
  cout << endl;
  delete[] a;
}
