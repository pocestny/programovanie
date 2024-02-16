#include <cmath>  // budeme pouzivat kniznicu cmath
#include <iostream>
using namespace std;

int n, l;
double r;

double x(int i) {
  return (double)(l) / 2.0 + r * cos((double)i * 2.0 * M_PI / (double)n);
}

double y(int i) {
  return (double)(l) / 2.0 + r * sin((double)i * 2.0 * M_PI / (double)n);
}

int main() {
  cin >> n;
  l = 800;
  r = 350;

  cout << "i " << l << " " << l << "\n";
  cout << "m " << x(0) << " " << y(0) << endl;
  for (int i = 1; i < n; i++) cout << "l " << x(i) << " " << y(i) << endl;
  cout << "l " << x(0) << " " << y(0) << endl;
  cout << "c 0 255 0\n";
  cout << "f " << l / 2 << " " << l / 2 << " 0 0 0 \n";
  cout << "s 61.png\n";
}
