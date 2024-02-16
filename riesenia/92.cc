#include "obrazok.h"
#include <iostream>
using namespace std;
using Int = unsigned long int;

int main() {
  Int N, R;
  int d;
  double stred_x, stred_y, m;
  cin >> R >> N >> d >> stred_x >> stred_y >> m;

  int obrazok[d][d];
  double pixel = 1 / ((double)d * m);

  for (int i = 0; i < d; i++)
    for (int j = 0; j < d; j++) {
      double cx = stred_x + (double)(j - d / 2) * pixel;
      double cy = stred_y + (double)(i - d / 2) * pixel;
      Int iter = 0;
      double x = cx, y = cy;
      while (x * x + y * y <= R * R && iter < N) {
        double nx = x * x - y * y + cx;
        y = 2 * x * y + cy;
        x = nx;
        iter++;
      }
      if (iter >= N)
        obrazok[i][j] = 0;
      else
        obrazok[i][j] = 1;
    }
  zapis_cb_png(d, d, obrazok, "82.png");
}
