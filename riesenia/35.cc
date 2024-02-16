#include "obrazok.h"
#include <iostream>
using namespace std;

int obr[100][100];

void stvorec(int r, int s, int d) {
  int i, j;
  for (i = r; i < r + d; i++)
    for (j = s; j < s + d; j++) obr[i][j] = 1;
}

int main() {
  int a, b, c;
  for (a = 0; a < 100; a++)
    for (b = 0; b < 100; b++) obr[a][b] = 0;

  cin >> a >> b >> c;
  stvorec(100 - a, 50 - a / 2, a);
  stvorec(100 - a - b, 50 - b / 2, b);
  stvorec(100 - a - b - c, 50 - c / 2, c);
  zapis_cb_png(100, 100, obr, "35.png");
}
