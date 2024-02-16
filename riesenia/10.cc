#include <iostream>
using namespace std;

int main() {
  int x, sum;
  sum = 0;

  cin >> x;
  while (x != -1) {
    sum = sum + x;
    cout << sum << endl;
    cin >> x;
  }
}
