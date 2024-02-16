#include <iostream>
using namespace std;

int B = 4201;

int max(int a, int b) {
  if (a > b)
    return a;
  else
    return b;
}

int main() {
  int n;
  cin >> n;
  int c[n], v[n];
  for (int i = 0; i < n; i++) cin >> c[i];
  for (int i = 0; i < n; i++) cin >> v[i];
  int m[B][n];
  for (int i = 0; i < B; i++) m[i][0] = 0;
  m[v[0]][0] = c[0];
  for (int i = 1; i < n; i++)
    for (int j = 0; j < B; j++) {
      m[j][i] = m[j][i - 1];
      if (v[i] <= j ) m[j][i] = max(m[j][i], c[i] + m[j - v[i]][i - 1]);
    }
  int res = 0;
  for (int i = 0; i < B; i++) res = max(res, m[i][n - 1]);
  cout << res << endl;
}
