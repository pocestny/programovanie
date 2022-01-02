#include <iostream>
using namespace std;

int main() {
  int i, j, n;
  cin >> n;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n - 1 - i; j++) cout << 0;
    for (j = 0; j < 2 * i + 1; j++) cout << 1;
    for (j = 0; j < n - 1 - i; j++) cout << 0;
    cout << endl;
  }
}
