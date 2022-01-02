#include <iostream>
using namespace std;

int main() {
  int x, sum = 0;

  while (true) {
    cin >> x;
    if (x == -1) break;
    sum = sum + x;
    cout << sum << endl;
  }
}
