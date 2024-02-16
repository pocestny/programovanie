#include <iostream>
using namespace std;

int main() {
  int i, j, n;
  cin >> n;
  int a[n];
  i = 0;
  while (i < n) {
    cin >> a[i];
    i = i + 1;
  }
  i = 0;
  j = n - 1;
  while (i <= j)
    if (a[i] > a[j]) {
      cout << 1 << endl;
      j--;
    } else if (a[i] < a[j]) {
      cout << -1 << endl;
      i++;
    } else {
      cout << 0 << endl;
      i++;
      j--;
    }
}
