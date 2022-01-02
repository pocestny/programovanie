#include <iostream>
using namespace std;

int main() {
  int x;
  int a, cnt = 0;

  cin >> a;
  while (true) {
    cin >> x;
    if (x == -1) break;
    if (x == a) cnt++;
  }
  cout << cnt << endl;
}
