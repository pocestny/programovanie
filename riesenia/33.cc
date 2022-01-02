#include <iostream>
using namespace std;

int a[100000];

int remove_max(int n) {
  int max, i, max_i;
  max = a[0];
  max_i = 0;
  for (i = 1; i < n; i++)
    if (a[i] > max) {
      max = a[i];
      max_i = i;
    }
  a[max_i] = -1;
  return max;
}

int main() {
  int i, n;
  cin >> n;
  for (i = 0; i < n; i++) cin >> a[i];
  for (i = 0; i < n; i++) cout << remove_max(n) << " ";
  cout << endl;
}
