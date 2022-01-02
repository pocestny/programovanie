#include <iostream>
using namespace std;
int main() {
  int n, x, s;
  s = 0;
  cin >> n;
  int i;
  while (n > 0) {
    cin >> x;
    s = s + x;
    n = n - 1;
  }
  cout << s << endl;
}
