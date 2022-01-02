#include "obrazok.h"
#include <iostream>

using namespace std;

int main() {
  int r, t;
  cin >> r >> t;
  int a[t][2 * t + 1];

  for (int i = 0; i < 2 * t + 1; i++) a[0][i] = 0;
  a[0][t] = 1;

  for (int i = 1; i < t; i++) {
    for (int j = 1; j < 2 * t; j++) {
      int b = 4 * a[i - 1][j - 1] + 2 * a[i - 1][j] + a[i - 1][j + 1];
      a[i][j] = (r & (1 << b)) ? 1 : 0;
    }
    a[i][0] = a[i][1];
    a[i][2 * t] = a[i][2 * t - 1];
  }

  for (int i = 0; i < t; i++)
    for (int j = 0; j < 2 * t + 1; j++) a[i][j] = 1 - a[i][j];
  zapis_cb_png(t, 2 * t + 1, a, "31.png");
}
