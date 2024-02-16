#include <iostream>
using namespace std;

int main() {
  int n, i, a, b, c;
  a = 0;
  b = 1;
  cin >> n;
  if (n < 3) {
    cout << n - 1 << endl;
  } else {
    i = 2;
    while (i < n) {
      c = a + b;
      a = b;
      b = c;
      i = i + 1;
    }
    cout << c << endl;
  }
}
