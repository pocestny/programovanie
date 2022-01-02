#include <iostream>
using namespace std;

int main() {
  int n, i, minx, maxx, miny, maxy, x, y, r;
  char prikaz[100];
  const int vela = 9999999;
  cin >> n;
  minx = vela;
  maxx = -vela;
  miny = vela;
  maxy = -vela;
  for (i = 0; i < n; i++) {
    cin >> prikaz;
    if (prikaz[0] == 'b') {
      cin >> x >> y;
      if (x < minx) minx = x;
      if (x > maxx) maxx = x;
      if (y < miny) miny = y;
      if (y > maxy) maxy = y;
    } else if (prikaz[0] == 'k') {
      cin >> x >> y >> r;
      if (x - r < minx) minx = x - r;
      if (x + r > maxx) maxx = x + r;
      if (y - r < miny) miny = y - r;
      if (y + r > maxy) maxy = y + r;
    } else {
      cin >> x >> y;
      if (x < minx) minx = x;
      if (x > maxx) maxx = x;
      if (y < miny) miny = y;
      if (y > maxy) maxy = y;
      cin >> x >> y;
      if (x < minx) minx = x;
      if (x > maxx) maxx = x;
      if (y < miny) miny = y;
      if (y > maxy) maxy = y;
    }
  }
  cout << minx << " " << miny << " " << maxx << " " << maxy << endl;
}
