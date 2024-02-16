#include "obrazok.h"
#include <iostream>
using namespace std;

int main() {
  int a, r;
  cin >> a >> r;
  int x[a][a];
  int i, j;
  for (i = 0; i < a; i++)
    for (j = 0; j < a; j++)
      if ((i - a / 2) * (i - a / 2) + (j - a / 2) * (j - a / 2) < r * r)
        x[i][j] = 0;
      else
        x[i][j] = 1;
  zapis_cb_png(a, a, x, "28.png");
}
