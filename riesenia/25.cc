#include "obrazok.h"
#include <iostream>
using namespace std;

int main() {
  int d;
  cin >> d;
  int a[d][d];
  int i, j;
  for (i = 0; i < d; i++)
    for (j = 0; j < d; j++)
      if (i < d - j)
        a[i][j] = 0;
      else
        a[i][j] = 1;
  zapis_cb_png(d, d, a, "25.png");
}
