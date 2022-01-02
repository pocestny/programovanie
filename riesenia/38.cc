#include <iostream>
using namespace std;

int a[100000];

void swap(int i, int j) {
  int k;
  k = a[i];
  a[i] = a[j];
  a[j] = k;
}

void perm(int i, int n) {
  int j;
  if (i == n - 1) {
    for (j = 0; j < n; j++) cout << a[j] << " ";
    cout << endl;
    return;
  }
  for (j = i; j < n; j++) {
    swap(i, j);
    perm(i + 1, n);
    swap(i, j);
  }
}

int main() {
  int i, n;
  cin >> n;
  for (i = 0; i < n; i++) a[i] = i + 1;
  perm(0, n);
}
