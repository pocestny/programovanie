#include <iostream>
using namespace std;

void otoc(int x, int y, int *a) {
  int i, k;
  int n = y + 1 - x;
  for (i = 0; i < n / 2; i++) {
    k = a[x + i];
    a[x + i] = a[x + n - i - 1];
    a[x + n - i - 1] = k;
  }
}

void posun(int n, int *a, int k) {
  k = k % n;
  otoc(0, n, a);
  otoc(0, n - k, a);
  otoc(n - k, n, a);
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
