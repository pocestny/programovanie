#include <iostream>
using namespace std;

int main() {
  int i, j, n;
  cin >> n;
  int a[n];
  for (i = 0; i < n; i++) cin >> a[i];
  int max = a[0], last = a[0];
  for (i = 1; i < n; i++) {
    if (a[i] > max) max = a[i];
    if (a[i] < last) last = a[i];
  }
  cout << last << endl;
  for (i = 1; i < n; i++) {
    int min = max;
    for (j = 0; j < n; j++)
      if (a[j] > last && a[j] < min) min = a[j];
    last = min;
    cout << last << endl;
  }
}
