#include <iostream>

using namespace std;

int main() {
  int r, c;
  cin >> r >> c;
  int m[2][c + 2];
  char s[c + 2];
  int i;
  for (i = 0; i < c + 2; i++) m[0][i] = 0;
  m[0][0] = 1;
  int curr = 1;
  while (r-- > 0) {
    cin >> s;
    m[curr][0] = 0;
    for (int i = 0; i < c; i++)
      if (s[i] == '#')
        m[curr][i + 1] = 0;
      else
        m[curr][i + 1] = m[curr][i] + m[1 - curr][i] + m[1 - curr][i + 1];
    curr = 1 - curr;
  }
  cout << m[1 - curr][c] << endl;
}
