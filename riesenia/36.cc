#include <iostream>
using namespace std;

void rot(int x) {
  if (x < 10)
    cout << x;
  else {
    cout << x % 10;
    rot(x / 10);
  }
}

int main() {
  int x;
  cin >> x;
  rot(x);
  cout << endl;
}
