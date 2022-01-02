#include "obrazok.h"
#include <iostream>
using namespace std;

int main() {
  int n, d;
  cin >> n >> d;
  int a[n][n];
  int i, j;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (i < d || i > n - d || j < d || j > n - d)
        a[i][j] = 0;
      else
        a[i][j] = 1;
  zapis_cb_png(n, n, a, "24.png");
}
