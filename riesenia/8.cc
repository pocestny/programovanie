#include <iostream>
using namespace std;

int main() {
  int x;
  int a, cnt;
  cnt = 0;
  cin >> a >> x;
  while (x != -1) {
    if (x == a) cnt = cnt + 1;
    cin >> x;
  }
  cout << cnt << endl;
}
