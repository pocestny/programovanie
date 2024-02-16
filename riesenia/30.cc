#include "obrazok.h"
#include <iostream>
using namespace std;

int main() {
  int t;
  cin >> t;
  int a[t][2 * t + 1];
  int i, j;
  for (i = 0; i < 2 * t + 1; i++) a[0][i] = 1;
  a[0][t] = 0;
  for (j = 1; j < t; j++) {
    a[j][0] = 1;
    a[j][2 * t] = 1;
    for (i = 1; i < 2 * t; i++) {
      int h;
      a[j][i] = 0;
      for (h = 0; h < 2; h++)
        if (a[j - 1][i - 1] == h && a[j - 1][i] == h && a[j - 1][i + 1] == h)
          a[j][i] = 1;
    }
  }
  zapis_cb_png(t, 2 * t + 1, a, "30.png");
}
