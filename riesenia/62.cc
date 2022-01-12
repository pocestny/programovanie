#include <iostream>
using namespace std;

void merge(int n, int *a, int m, int *b, int *p) {
  int i = 0, j = 0, k;
  for (k = 0; k < n + m; k++)
    if (i < n && (j == m || a[i] < b[j])) {
      p[k] = a[i];
      i++;
    } else {
      p[k] = b[j];
      j++;
    }
}

void sort(int n, int *a) {
  if (n <= 1) return;
  int i, x = n / 2, y = n - x;
  int *b = new int[x];
  int *c = new int[y];
  for (i = 0; i < x; i++) b[i] = a[i];
  for (i = 0; i < y; i++) c[i] = a[i + x];
  sort(x, b);
  sort(y, c);
  merge(x, b, y, c, a);
  delete[] b;
  delete[] c;
}

int main() {
  int n, *a;
  cin >> n;
  a = new int[n];
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(n, a);
  for (int i = 0; i < n; i++) cout << a[i] << " ";
  cout << endl;
  delete[] a;
}
