#include <iostream>
using namespace std;

int main() {
  int x;

  while (true) {
    cin >> x;
    if (x == -1) break;
    if (x % 2 == 0)
      cout << x << endl;
    else
      cout << x + 1 << endl;
  }
}
