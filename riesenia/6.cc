#include <iostream>
using namespace std;

int main() {
  int x;
  cin >> x;

  while (x != -1) {
    if (x % 2 == 0)
      cout << x << endl;
    else
      cout << x + 1 << endl;
    cin >> x;
  }
}
