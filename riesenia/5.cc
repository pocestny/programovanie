#include <iostream>
using namespace std;
int main() {
  int n,  s;
  s = 0;
  cin >> n;

  // stacilo by iba
  // cout << n * (n + 1) / 2 << endl;

  int i;
  while (n > 0) {
    s = s + n;
    n = n - 1;
  }
  cout << s << endl;
}


