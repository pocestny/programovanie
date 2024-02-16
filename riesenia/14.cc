#include <iostream>
using namespace std;

int main() {
  int i, j, n;
  cin >> n;
  i = 0;
  while (i < n) {
    j = 0;
    while (j < n - 1 - i) {
      cout << 0;
      j = j + 1;
    }
    j = 0;
    while (j < 2 * i + 1) {
      cout << 1;
      j = j + 1;
    }
    j = 0;
    while (j < n - 1 - i) {
      cout << 0;
      j = j + 1;
    }
    cout << endl;
    i = i + 1;
  }
}
