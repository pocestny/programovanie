#include <iostream>
using namespace std;

int main() {
  char s[10000], n = 0;
  int val[10000], m = 0;
  char c;

  while (true) {
    cin >> c;
    if (c == '$') break;
    if (c >= '0' && c <= '9') {
      val[m] = c - '0';
      m++;
      c = '.';
    }
    s[n] = c;
    n++;
    while (n >= 5 && s[n - 1] == ')' && s[n - 2] == '.' &&
           (s[n - 3] == '+' || s[n - 3] == '*') && s[n - 4] == '.' &&
           s[n - 5] == '(') {
      int v;
      if (s[n - 3] == '+')
        v = val[m - 1] + val[m - 2];
      else
        v = val[m - 1] * val[m - 2];
      m--;
      val[m - 1] = v;
      n = n - 4;
      s[n - 1] = '.';
    }
  }
  cout << val[0] << endl;
}
