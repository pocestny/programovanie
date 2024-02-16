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
  int s;
  cin >> n >> s;
  l = 800;
  r = 350;
  cout << "i " << l << " " << l << "\n";
  cout << "m " << x(0) << " " << y(0) << endl;
  for (int i = 1; i < n; i++)
    cout << "l " << x(s * i) << " " << y(s * i) << endl;
  cout << "l " << x(0) << " " << y(0) << endl;
  cout << "c 255 255 0\n";
  cout << "f " << l / 2 << " " << l / 2 << " 0 0 0 \n";
  r = 0.9 * r;
  cout << "c 255 0 0 ";
  for (int i = 0; i < n; i++)
    cout << "f " << x(i) << " " << y(i) << " 0 0 0" << endl;
  cout << "s 62.png\n";
}
