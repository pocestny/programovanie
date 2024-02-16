#include <iostream>
using namespace std;

int main() {
  int i, j, n;
  cin >> n;
  i = 0;
  while (i <= n) {
    j = 0;
    while (j < n - i) {
      cout << 0;
      j = j + 1;
    }
    j = 0;
    while (j < i) {
      cout << 1;
      j = j + 1;
    }
    cout << endl;
    i = i + 1;
  }
}
