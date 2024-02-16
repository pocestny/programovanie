#include <iostream>
using namespace std;

int main() {
  int n, t;
  cin >> n >> t;
  int a[2][2 * n + 1];
  int i, curr = 0;
  for (i = 0; i < 2 * n + 1; i++) a[0][i] = 0;
  a[0][n] = 1;
  a[1][0] = 0;
  a[1][2 * n] = 0;
  while (t > 0) {
    for (i = 1; i < 2 * n; i++) {
      int h;
      a[1 - curr][i] = 1;
      for (h = 0; h < 2; h++)
        if (a[curr][i - 1] == h && a[curr][i] == h && a[curr][i + 1] == h)
          a[1 - curr][i] = 0;
    }
    t--;
    curr = 1 - curr;
  }
  for (i = 0; i < 2 * n + 1; i++)
    if (a[curr][i] == 1)
      cout << "*";
    else
      cout << ".";
  cout << endl;
}
