#include <iostream>

using namespace std;
double f;
int d;

void sq(double x, double y, double s, int c) {
  cout << "c 255 " << c << " 0" << endl;
  cout << "m " << x - s / 2 << " " << y - s / 2 << endl;
  cout << "l " << x + s / 2 << " " << y - s / 2 << endl;
  cout << "l " << x + s / 2 << " " << y + s / 2 << endl;
  cout << "l " << x - s / 2 << " " << y + s / 2 << endl;
  cout << "l " << x - s / 2 << " " << y - s / 2 << endl;
  cout << "f " << x << " " << y << " 255 " << c << " 0" << endl;
}

void doit(double x, double y, double s, int dg) {
  int c = (int)((double)(dg)*120.0 / (double)(d));
  sq(x, y, s, c);
  if (dg < d) {
    doit(x - s / 2, y - s / 2, f * s, dg + 1);
    doit(x - s / 2, y + s / 2, f * s, dg + 1);
    doit(x + s / 2, y + s / 2, f * s, dg + 1);
    doit(x + s / 2, y - s / 2, f * s, dg + 1);
  }
}

int main() {
  int x;
  double ix;
  cin >> x >> d >> ix >> f;
  cout << "i " << x << " " << x << endl;
  doit((double)x / 2.0, (double)x / 2.0, ix * x, 0);
  cout << "s 60.png" << endl;
  ;
}
