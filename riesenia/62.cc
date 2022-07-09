#include <cmath>
#include <iostream>
using namespace std;

bool test(int p) {
  int i;
  for (i = 2; i <= sqrt(p); i++)
    if (p % i == 0) return false;
  return true;
}

int *prvocisla(int n) {
  int *a = new int[n];
  int i, p = 2;
  for (i = 0; i < n; i++) {
    while (!test(p)) p++;
    a[i] = p;
    p++;
  }
  return a;
}

int main() {
  int n;
  cin >> n;
  int *a = prvocisla(n);
  int i;
  for (i = 0; i < n; i++) cout << a[i] << " ";
  cout << endl;
  delete[] a;
}
