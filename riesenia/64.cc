#include <iostream>
using namespace std;

struct Bod {
  float x, y;
};

void vymen(int i, int j, Bod *a) {
  Bod x;
  x = a[i];
  a[i] = a[j];
  a[j] = x;
}

void InsertSort(int n, Bod *a) {
  int i, j;
  for (i = 1; i < n; i++)
    for (j = i; j > 0 && a[j - 1].x > a[j].x; j--) vymen(j - 1, j, a);
}

int main() {
  int n;
  cin >> n;
  Bod *a = new Bod[n];
  int i;
  for (i = 0; i < n; i++) cin >> a[i].x >> a[i].y;
  InsertSort(n, a);
  for (i = 0; i < n; i++) cout << "[" << a[i].x << " " << a[i].y << "]" << endl;
  delete[] a;
}
