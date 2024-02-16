#include <iostream>
using namespace std;

int *kopiruj(int n, int *a) {
  int *p = new int[n];
  int i;
  for (i = 0; i < n; i++) p[i] = a[i];
  return p;
}

int main() {
  int n, *a;
  cin >> n;
  a = new int[n];
  int i;
  for (i = 0; i < n; i++) cin >> a[i];
  int *p = kopiruj(n, a);
  for (i = 0; i < n; i++) cout << p[i] << " ";
  cout << endl;
  delete[] a;
  delete[] p;
}
