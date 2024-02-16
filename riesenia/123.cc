#include <cstdlib>
#include <iostream>

#include "tabulka.h"

using namespace std;
const int m = 64;

struct HashFunc {
  Tabulka<unsigned char> T;
  int b;

  HashFunc(int _b, unsigned long seed) : b{_b}, T(_b, m) {
    srandom(seed);
    for (int i = 0; i < b; i++)
      for (int j = 0; j < m; j++) T(i, j) = random() % 2;
  }

  int operator()(unsigned long x) {
    int res = 0;
    for (int i = 0; i < b; i++)
      for (int j = 0; j < m; j++)
        if (T(i, j) && (x & (1 << (m - 1 - j)))) res ^= 1 << (b - 1 - i);
    return res;
  }
};

ostream &operator<<(ostream &str, const HashFunc &H) {
  for (int i = 0; i < H.b; i++) {
    for (int j = 0; j < m; j++) str << (int)H.T(i, j) << " ";
    str << endl;
  }
  return str;
}

int main() {
  int b, n;
  unsigned long seed;
  cin >> b >> seed >> n;
  HashFunc H(b, seed);
  cout << H << endl << endl;
  while (n-- > 0) {
    unsigned long x;
    cin >> x;
    cout << "H(" << x << ") = " << H(x) << endl;
  }
}
