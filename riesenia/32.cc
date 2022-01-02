#include <iostream>
using namespace std;

int max(int a, int b, int c) {
  if (a > b) {
    if (a > c)
      return a;
    else
      return c;
  } else {
    if (b > c)
      return b;
    else
      return c;
  }
}

int main() {
  int i, j, k;
  cin >> i >> j >> k;
  cout << max(i, j, k) << endl;
}
