#include <iostream>
using namespace std;

int *merge(int n, int *a, int m, int *b) {
  int *p = new int[n + m];
  int i = 0, j = 0, k;
  for (k = 0; k < n + m; k++)
    if (i < n && (j == m || a[i] < b[j])) {
      p[k] = a[i];
      i++;
    } else {
      p[k] = b[j];
      j++;
    }
  return p;
}

int main() {
  int n, m, *a, *b, i;
  cin >> n;
  a = new int[n];
  for (i = 0; i < n; i++) cin >> a[i];
  cin >> m;
  b = new int[m];
  for (i = 0; i < m; i++) cin >> b[i];
  int *p = merge(n, a, m, b);
  for (i = 0; i < n + m; i++) cout << p[i] << " ";
  cout << endl;
  delete[] a;
  delete[] b;
  delete[] p;
}
