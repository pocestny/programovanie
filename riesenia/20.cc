#include <iostream>
using namespace std;

int main() {
  int n;
  cin >> n;
  int i, j, a[n + 1];
  for (i = 0; i < n; i++) cin >> a[i];
  a[n] = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n - i; j++) {
      cout << a[j] << " ";
      a[j] = a[j] + a[j + 1];
    }
    cout << endl;
  }
}
