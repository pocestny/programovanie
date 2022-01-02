#include <iostream>
using namespace std;

int main() {
  int n, i, a = 0, b = 1, c;
  cin >> n;
  if (n < 3) {
    cout << n - 1 << endl;
  } else {
    for (i = 2; i < n; i++) {
      c = a + b;
      a = b;
      b = c;
    }
    cout << c << endl;
  }
}
