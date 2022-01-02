#include "obrazok.h"
#include <iostream>
using namespace std;

int main() {
  int d;
  cin >> d;
  int a[8 * d][8 * d];
  int i, j;
  for (i = 0; i < 8 * d; i++)
    for (j = 0; j < 8 * d; j++)
      if (((i / d) + (j / d)) % 2 == 1)
        a[i][j] = 1;
      else
        a[i][j] = 0;
  zapis_cb_png(8 * d, 8 * d, a, "27.png");
}
