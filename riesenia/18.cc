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
  int max, last;
  max = a[0];
  last = a[0];
  i = 1;
  while (i < n) {
    if (a[i] > max) max = a[i];
    if (a[i] < last) last = a[i];
    i = i + 1;
  }
  cout << last << endl;
  i = 1;
  while (i < n) {
    int min;
    min = max;
    int j;
    j = 0;
    while (j < n) {
      if (a[j] > last && a[j] < min) min = a[j];
      j = j + 1;
    }
    last = min;
    cout << last << endl;
    i = i + 1;
  }
}
