#include <iostream>
using namespace std;

void otoc(int n, int *a) {
  int i, k;
  for (i = 0; i < n / 2; i++) {
    k = a[i];
    a[i] = a[n - i - 1];
    a[n - i - 1] = k;
  }
}

int main() {
  int n, *a;
  cin >> n;
  a = new int[n];
  int i;
  for (i = 0; i < n; i++) cin >> a[i];
  otoc(n, a);
  for (i = 0; i < n; i++) cout << a[i] << " ";
  cout << endl;
  delete[] a;
}
