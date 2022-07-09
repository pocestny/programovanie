#include <iostream>
using namespace std;

int main() {
  int s[200], n = 0, x;
  cin >> x;
  while (x > 0) {
    s[n] = x % 2;
    x = x / 2;
    n++;
  }
  while (n > 0) {
    n--;
    cout << s[n];
  }
  cout << endl;
}
