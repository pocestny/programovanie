#include <iostream>
using namespace std;

char a[10000];
int n;
int m[10000][10000], l[10000][10000], r[10000][10000];

void vypis(int i, int j) {
  if (i > j) return;
  if (m[i][j] == 1) {
    cout << a[i];
    return;
  }
  if (a[i] == a[j]) {
    cout << a[i];
    vypis(i + 1, j - 1);
    cout << a[j];
  } else
    vypis(l[i][j], r[i][j]);
}

int main() {
  cin >> a;
  n = 0;
  while (a[n] != 0) n++;
  for (int i = 0; i < n; i++) m[i][i] = 1;

  for (int d = 1; d < n; d++)
    for (int i = 0; i < n; i++)
      if (i + d < n) {
        int j = i + d;

        if (a[i] == a[j]) {
          m[i][j] = 2;
          if (d > 1) {
            l[i][j] = i + 1;
            r[i][j] = j - 1;
            m[i][j] += m[i + 1][j - 1];
          }
        } else {
          m[i][j] = 1;
          if (d > 1) {
            m[i][j] = m[i + 1][j - 1];
            l[i][j] = i + 1;
            r[i][j] = j - 1;
            if (m[i][j - 1] > m[i][j]) {
              m[i][j] = m[i][j - 1];
              l[i][j] = i;
              r[i][j] = j - 1;
            }
            if (m[i + 1][j] > m[i][j]) {
              m[i][j] = m[i + 1][j];
              l[i][j] = i + 1;
              r[i][j] = j;
            }
          }
        }
      }

  vypis(0, n - 1);
  cout << endl;
}
