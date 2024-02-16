#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;
  // m[curr][0][x] = kolko je moznosti pre  a[i]=x, ak nalavo je mensi
  int m[2][2][201];
  int curr = 0;
  for (int i = 0; i <= 200; i++) m[1][0][i] = m[1][1][i] = 0;
  m[1][0][0] = 1;

  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    for (int j = 0; j <= 200; j++) m[curr][0][j] = m[curr][1][j] = 0;
    int l = x, r = x;
    if (x == -1) {
      l = 1;
      r = 200;
    }

    for (int j = 0; j < l; j++)
      m[curr][0][l] += m[1 - curr][0][j] + m[1 - curr][1][j];
    for (int j = l + 1; j <= r; j++)
      m[curr][0][j] =
          m[curr][0][j - 1] + m[1 - curr][0][j - 1] + m[1 - curr][1][j - 1];

    int s = 0;
    for (int j = 200; j > r; j--) s += m[1 - curr][1][j];
    for (int j = r; j >= l; j--) {
      s += m[1 - curr][1][j];
      m[curr][1][j] = s + m[1 - curr][0][j];
    }

    curr = 1 - curr;
  }

  curr = 1 - curr;
  int s = 0;
  for (int i = 1; i <= 200; i++) s += m[curr][1][i];
  cout << s << endl;
}
