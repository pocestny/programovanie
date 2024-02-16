#include <iostream>
using namespace std;

int main() {
  int i, n;
  cin >> n;
  int x[n];
  i = 0;
  while (i < n) {
    cin >> x[i];
    i = i + 1;
  }
  int a;
  cin >> a;
  i = 0;
  while (i < n) {
    cout << x[i] + a << endl;
    i = i + 1;
  }
}
