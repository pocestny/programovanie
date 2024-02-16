#include "obrazok.h"
#include <iostream>
using namespace std;

struct Farba {
  unsigned char r, g, b, a;
};

const int N = 1000;
Farba obr[N][N], pen = {0, 0, 0, 255};
int r, s;
double x = 0, y = 0;

void put(double x, double y) { obr[r - (int)y][(int)x] = pen; }

double av(double x) {
  if (x > 0) return x;
  return -x;
}

bool rovnasa(Farba f1, Farba f2) {
  if (f1.r == f2.r && f1.g == f2.g && f1.b == f2.b) return true;
  return false;
}

void line(double x1, double y1, double x2, double y2) {
  if (av(x2 - x1) < 0.00001) {
    if (y1 > y2) {
      int k = y1;
      y1 = y2;
      y2 = k;
    }
    for (int i = y1; i <= y2; i++) put(x1, i);
    return;
  }
  if (av(y2 - y1) < 0.00001) {
    if (x1 > x2) {
      int k = x1;
      x1 = x2;
      x2 = k;
    }
    for (int i = x1; i <= x2; i++) put(i, y1);
    return;
  }
  if (x1 > x2) {
    int k = x1;
    x1 = x2;
    x2 = k;
    k = y1;
    y1 = y2;
    y2 = k;
  }
  double s = (y2 - y1) / (x2 - x1);
  if (s >= -1 && s <= 1) {
    double dx = ((int)x1) + 0.5 - x1;
    for (int i = 0; i < (int)x2 - (int)x1; i++)
      put(x1 + 0.5 + i, y1 + (dx + i) * s);
  } else {
    if (y1 > y2) {
      int k = x1;
      x1 = x2;
      x2 = k;
      k = y1;
      y1 = y2;
      y2 = k;
    }
    s = 1 / s;
    double dy = ((int)y1) + 0.5 - y1;
    for (int i = 0; i < (int)y2 - (int)y1; i++)
      put(x1 + (dy + i) * s, y1 + 0.5 + i);
  }
}

void fill(int ir, int is, const Farba &b) {
  if (ir < 0 || ir > r || is < 0 || is > s) return;
  if (rovnasa(obr[ir][is], b) || rovnasa(obr[ir][is], pen)) return;
  obr[ir][is] = pen;
  fill(ir - 1, is, b);
  fill(ir + 1, is, b);
  fill(ir, is - 1, b);
  fill(ir, is + 1, b);
}

int main() {
  char prikaz[100];

  while (1) {
    cin >> prikaz;
    if (prikaz[0] == 'i') {
      cin >> s >> r;
      for (int i = 0; i < r; i++)
        for (int j = 0; j < s; j++) obr[i][j] = {255, 255, 255, 255};
    } else if (prikaz[0] == 's') {
      cin >> prikaz;
      zapis_rgba_png_vyrez(N, N, obr, prikaz, 0, 0, r, s);
      break;
    } else if (prikaz[0] == 'm') {
      cin >> x >> y;
    } else if (prikaz[0] == 'l') {
      double x1, y1, x2, y2;
      x1 = x;
      y1 = y;
      cin >> x2 >> y2;
      x = x2;
      y = y2;
      line(x1, y1, x2, y2);
    } else if (prikaz[0] == 'c') {
      int rr, gg, bb;
      cin >> rr >> gg >> bb;
      pen = {(unsigned char)rr, (unsigned char)gg, (unsigned char)bb, 255};
    } else if (prikaz[0] == 'f') {
      int rr, gg, bb;
      double x, y;
      cin >> x >> y >> rr >> gg >> bb;
      fill(r - (int)y, (int)x,
           Farba{(unsigned char)rr, (unsigned char)gg, (unsigned char)bb});
    }
  }
}
