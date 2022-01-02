#include <iostream>
using namespace std;

int main() {
  int cnt = 0, max = 0;
  int x;
  cin >> x;
  while (x > 1) {
    cnt++;
    if (x > max) max = x;
    if (x % 2 == 0)
      x = x / 2;
    else
      x = 3 * x + 1;
  }
  cout << cnt << endl;
  cout << max << endl;
}
