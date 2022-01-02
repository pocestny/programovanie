#include <iostream>
using namespace std;

int main() {
  int i, n;
  cin >> n;
  int x[n];
  for (i = 0; i < n; i++) cin >> x[i];
  int a;
  cin >> a;
  for (i = 0; i < n; i++) cout << x[i] + a << endl;
}
