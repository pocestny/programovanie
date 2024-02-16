#include "obrazok.h"
#include <iostream>
using namespace std;

const int N = 10000;
int a[N][N];

void sierp(int r, int s, int d, int n) {
  if (d == 0) {
    a[r][s] = 0;
    return;
  }
  int i, j;
  n = n / 3;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      if (i != 1 || j != 1) sierp(r + n * i, s + n * j, d - 1, n);
}

int main() {
  int d, i, j, n;
  cin >> d;
  n = 1;
  for (i = 0; i < d; i++) n = 3 * n;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) a[i][j] = 1;
  sierp(0, 0, d, n);
  zapis_cb_png_vyrez(N, N, a, "42.png", 0, 0, n, n);
}
